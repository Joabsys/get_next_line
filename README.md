*Este projeto foi criado como parte do currículo da 42 por [jesequie].*

---

## Descrição

**get_next_line** é um projeto do currículo da 42 que consiste em escrever uma função capaz de ler um arquivo de texto linha por linha, independentemente do tamanho do arquivo ou do tamanho do buffer de leitura utilizado internamente. A função deve ser chamada repetidamente, retornando uma linha por chamada, e deve manter o controle de qualquer dado restante entre chamadas sem reler o arquivo desde o início.

Esta implementação cobre apenas a **parte obrigatória** (um único descritor de arquivo por vez). A parte bônus (múltiplos descritores de arquivo simultaneamente) não foi implementada.

### Funções implementadas

**Função principal:**

| Função | Arquivo | Descrição |
|---|---|---|
| `get_next_line` | get_next_line.c | Retorna a próxima linha lida a partir de `fd`, uma chamada por vez |

**Função auxiliar interna:**

| Função | Descrição |
|---|---|
| `fill_stash`   | Lê do `fd` em blocos de `BUFFER_SIZE` bytes, adicionando cada bloco ao stash, até encontrar um `'\n'` ou `read` chegar ao EOF/erro |
| `extract_line` | get_next_line_utils.c | Aloca um novo buffer e copia o conteúdo do stash até o `'\n'` (inclusive) |
| `update_stash` | get_next_line_utils.c | Aloca um novo buffer com o que sobrou no stash após a linha extraída, depois libera o stash antigo |

**Funções utilitárias:**

| Função | Arquivo | Descrição |
|---|---|---|
| `find_char` | get_next_line_utils.c | Retorna o índice de um caractere em uma string, ou seu comprimento caso o caractere não seja encontrado |
| `ft_strlen` | get_next_line_utils.c | Retorna o comprimento de uma string (reimplementação local — libft não é permitida neste projeto) |
| `add_chunk` | get_next_line_utils.c | Aloca um novo buffer combinando o stash existente com o bloco recém-lido, depois libera o stash antigo |


---

## Instruções

### Requisitos

- Compilador `cc`
- Sistema operacional baseado em Unix (Linux ou macOS)

### Compilação

Clone o repositório:

```bash
git clone https://github.com/Joabsys/get_next_line.git
cd get_next_line
```

Como a parte obrigatória não exige Makefile, compile diretamente com o `BUFFER_SIZE` de sua escolha passado como flag:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```
### Verificando vazamento de memoria
```bash
valgrind --leak-check=full --show-leak-kinds=all ./seu_progama
```

### Usando get_next_line no seu projeto

Copie `get_next_line.c`, `get_next_line_utils.c` e `get_next_line.h` para o seu projeto, inclua o header e compile com o `BUFFER_SIZE` desejado:

```bash
cc -D BUFFER_SIZE=42 seu_arquivo.c get_next_line.c get_next_line_utils.c -o seu_programa
```

---

## Algoritmo e Estrutura de Dados

### Visão geral

`get_next_line` existe para resolver uma restrição: uma linha pode ser maior ou menor que `BUFFER_SIZE`, e um único bloco lido com `read()` pode conter mais de uma linha — ou apenas parte de uma. Para resolver isso, a função mantém um **buffer persistente (o stash)** entre chamadas, declarado como `static`, para que sobreviva após o retorno da função.

Cada chamada segue as mesmas três etapas:

```
1. fill_stash   → lê do fd em blocos de BUFFER_SIZE até encontrar '\n' ou EOF
2. extract_line → copia do início do stash até o '\n' (inclusive)
3. update_stash → guarda o que sobrou após o '\n' para a PRÓXIMA chamada
```

### Por que o stash precisa ser `static`

Sem `static`, o stash seria resetado a cada chamada, e qualquer dado lido além do `'\n'` da linha atual seria perdido — a próxima chamada não teria como saber que aquele trecho já havia sido lido do arquivo.

### Execução passo a passo (exemplo)

Dado um arquivo contendo `"hello\nworld\n"` e `BUFFER_SIZE = 4`:

```
Chamada 1: get_next_line(fd)

  stash = ""                       (static, começa vazio)
  read → chunk = "hell"  → stash = "hell"
  sem '\n' → read → chunk = "o\nwo" → stash = "hello\nwo"
  encontrou '\n' no índice 5

  extract_line  → retorna "hello\n"
  update_stash  → stash vira "wo"

  → retorna "hello\n"

Chamada 2: get_next_line(fd)

  stash = "wo"                     (sobrou da chamada 1)
  sem '\n' → read → chunk = "rld\n" → stash = "world\n"
  encontrou '\n' no índice 5

  extract_line  → retorna "world\n"
  update_stash  → stash vira ""

  → retorna "world\n"

Chamada 3: get_next_line(fd)

  read retorna 0 (EOF), stash vazio → retorna NULL
```
## Main exemplo para testes
---
```
#include<stdio.h>
#include<fcntl.h>
#include"get_next_line.h"
int main()
{
int fd;
char *line;

	fd = open("texto.txt",O_RDONLY);

	while((line = get_next_line(fd)))
	{
		printf("%s",line);
		free(line);
	}
	close(fd);
	return(0);
}
```

### Por que o stash e o chunk são alocados dinamicamente

Um array de tamanho fixo (`char stash[BUFFER_SIZE + 1]`) falha em dois casos:

- **`BUFFER_SIZE` muito pequeno (ex: `1`)** — uma linha maior que o array causaria overflow.
- **`BUFFER_SIZE` muito grande (ex: `10000000`)** — um array local desse tamanho na stack causa stack overflow.

Alocar tanto o `chunk` quanto o stash na heap com `malloc`, e realocar o stash (cópia + free) sempre que novos dados são adicionados ou extraídos, torna a função correta para qualquer valor de `BUFFER_SIZE`, de `1` até vários milhões, sem depender do tamanho real de uma linha no arquivo.

### Valor de retorno

`get_next_line` retorna uma string recém-alocada contendo a próxima linha (incluindo o `'\n'` final, se presente), ou `NULL` quando não há mais nada para ler (EOF com stash vazio) ou quando ocorre um erro. O chamador é responsável por liberar a linha retornada com `free`.

---

## Recursos

### Documentação e Referências

- [man pages online — read(2)](https://man7.org/linux/man-pages/man2/read.2.html) — página de manual oficial da syscall `read` usada para preencher o stash
- [man pages online — malloc(3)](https://man7.org/linux/man-pages/man3/malloc.3.html) — página de manual oficial para alocação dinâmica de memória
- [Referência da Biblioteca Padrão C — cppreference.com](https://en.cppreference.com/w/c) — referência para funções C padrão e duração de armazenamento `static`
- [42 Docs — Norminette](https://github.com/42School/norminette) — subject do projeto e regras da Norminette

### Uso de IA

**Claude (Anthropic)** foi utilizado durante o desenvolvimento deste projeto para os seguintes fins:

- **Esclarecimento conceitual** — entender como um buffer `static` persiste dados entre chamadas separadas de uma função, e como dividir a lógicachunk de leitura de arquivo em um stash que acumula blocos e uma etapa de extração por chamada
- **Auxílio na depuração** — identificar problemas com avanço de ponteiro dentro do stash, um crash `free(): invalid pointer` causado por um parêntese mal posicionado no tamanho de alocação, e um segfault em arquivos vazios causado por desreferenciamento de stash `NULL`
- **Escrita do README** — estruturação e redação deste arquivo de documentação

> A IA foi utilizada exclusivamente como ferramenta de aprendizado e apoio. Todo o código foi escrito e compreendido pelo autor.

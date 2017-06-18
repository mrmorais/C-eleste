#### Celeste

A (not so much) smart snake solver.

Este projeto foi desenvolvido por Maradona Morais e Franklin Matheus como requisito do Professor Selan Rodrigues dos Santos (no curso Estruturas de Dados I, semestre 2017.1, IMD, UFRN). Celeste é uma cobra autonoma que resolve sozinha um labirinto, dado pelo usuário, buscando por maçãs para conseguir pontos.

Este vídeo, no YouTube, mostra o funcionamento deste software: https://www.youtube.com/watch?v=4H9tBkkyHjg

### Requisitos

A Celeste possui interface gráfica para interação visual. Por isso, é necessário instalar a biblioteca de multimídia utilizada **SFML (Simple and Fast Multimidia Library)** ([download](https://www.sfml-dev.org/download/sfml/2.4.2/)).

### Building and Running

Para fazer a compilação do projeto é utilizado a ferramenta **cmake** ([download](https://cmake.org/download/)). Com o cmake instalado execute os seguintes comandos no terminal:

```bash
$ mkdir build 
$ sh compile.sh
```

Após a conclusão da compilação o arquivo executável `Celeste` será construído no diretório `build`, para executar faça:

```bash
$ ./build/Celeste
```

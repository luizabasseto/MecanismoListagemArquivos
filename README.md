# Trabalho Prático: Mecanismo de Indexação e Busca

Trabalho realizado como parte de avaliação da disciplina de Algoritmos e Estruturas de Dados 2

**Aluna:** Luiza Batista Basseto - **RA:** 2251825

## Descrição

Este projeto implementa uma máquina de busca em C++ capaz de indexar arquivos 
de texto (.txt) e realizar consultas eficientes utilizando um Índice Invertido.

O sistema opera em dois modos:
1. Indexação: Lê arquivos, processa o texto, remove stopwords e salva os dados.
2. Busca: Carrega os dados e realiza consultas booleanas (AND) por palavras-chave.

## Estrutura do Projeto
``` cmd
- index/
- indexer/
- library/
- textProcessor/
- serializer/
- queryProcessor/
- main.cpp
```
## Como compilar

Para compilar o projeto, abra o terminal na raiz do diretório e execute:

    make

Isso gerará o executável chamado 'indice'.

Para limpar os arquivos objeto (.o) e o executável gerado:

    make clean

### Executando o projeto

1. Modo de Indexação (Construção)
   Varre um diretório, processa os arquivos .txt e gera o arquivo 'index.dat'.
   
   ```Sintaxe: ./indice construir <caminho_do_diretorio>```
   
   Exemplo:
   ```$ ./indice construir library```

2. Modo de Busca (Consulta)
   Carrega o índice da memória e busca documentos que contenham TODOS os termos.
   
   ```Sintaxe: ./indice buscar <termo1> [termo2] ... [termoN]```
   
   Exemplo (Busca simples):
   ```$ ./indice buscar dom```

   Exemplo (Busca composta - AND):
   ```$ ./indice buscar dom casmurro capitu```


## Requisitos para o sistema
- Sistema Operacional: Linux (Ubuntu 20.04 ou superior) ou WSL no Windows.
- Compilador: g++ com suporte a C++17 (necessário para <filesystem>).
- Ferramenta de construção: GNU Make.

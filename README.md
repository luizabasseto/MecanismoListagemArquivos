# Trabalho Prático: Mecanismo de Indexação e Busca

## Trabalho realizado como parte de avaliação da disciplina de Algoritmos e Estruturas de Dados 2

# Aluna

DESCRIÇÃO
---------------------------------------------------------------------------
Este projeto implementa uma máquina de busca em C++ capaz de indexar arquivos 
de texto (.txt) e realizar consultas eficientes utilizando um Índice Invertido.

O sistema opera em dois modos:
1. Indexação: Lê arquivos, processa o texto, remove stopwords e salva os dados.
2. Busca: Carrega os dados e realiza consultas booleanas (AND) por palavras-chave.

REQUISITOS DE SISTEMA
---------------------------------------------------------------------------
- Sistema Operacional: Linux (Ubuntu 20.04 ou superior) ou WSL no Windows.
- Compilador: g++ com suporte a C++17 (necessário para <filesystem>).
- Ferramenta de construção: GNU Make.

ESTRUTURA DO PROJETO
---------------------------------------------------------------------------
O código foi modularizado seguindo o padrão de responsabilidade única:

- index/          -> Classe Index: Estruturas de dados (Mapas e Sets).
- indexer/        -> Classe Indexer: Leitura de diretórios e orquestração.
- textProcessor/  -> Classe TextProcessor: Normalização e limpeza de strings.
- serializer/     -> Classe Serializer: Leitura/Escrita binária manual.
- queryProcessor/ -> Classe QueryProcessor: Lógica de busca e interseção.
- main.cpp        -> Interface de Linha de Comando (CLI).
- stopwords.txt   -> Lista de palavras a serem ignoradas na indexação.

COMPILAÇÃO
---------------------------------------------------------------------------
Para compilar o projeto, abra o terminal na raiz do diretório e execute:

    make

Isso gerará o executável binário chamado 'indice'.

Para limpar os arquivos objeto (.o) e o executável gerado:

    make clean

EXECUÇÃO
---------------------------------------------------------------------------

1. MODO INDEXAÇÃO (CONSTRUIR)
   Varrre um diretório, processa os arquivos .txt e gera o arquivo 'index.dat'.
   
   Sintaxe: ./indice construir <caminho_do_diretorio>
   
   Exemplo:
   $ ./indice construir library

   Observação: O arquivo 'stopwords.txt' deve estar acessível. O sistema
   grava o caminho absoluto das stopwords para garantir consistência na busca.

2. MODO BUSCA (CONSULTAR)
   Carrega o índice da memória e busca documentos que contenham TODOS os termos.
   
   Sintaxe: ./indice buscar <termo1> [termo2] ... [termoN]
   
   Exemplo (Busca simples):
   $ ./indice buscar dom

   Exemplo (Busca composta - AND):
   $ ./indice buscar dom casmurro capitu

DECISÕES DE PROJETO E IMPLEMENTAÇÃO
---------------------------------------------------------------------------
1. Estrutura de Dados: 
   Utilizou-se 'std::unordered_map' para o índice invertido, garantindo complexidade 
   média O(1) no acesso às palavras. Os valores são armazenados em 'std::set<int>',
   o que mantém os IDs dos documentos ordenados e sem duplicatas.

2. Interseção Manual (Busca Eficiente):
   Conforme requisito, a interseção de listas para buscas múltiplas foi implementada 
   manualmente. Utilizou-se a técnica de "Two Pointers" (Dois Ponteiros) aproveitando 
   que os std::set já estão ordenados. Isso garante uma complexidade linear O(N+M) 
   na comparação das listas, muito superior a loops aninhados O(N*M).

3. Serialização Binária:
   A persistência dos dados em 'index.dat' é feita byte-a-byte (modo binário) 
   sem bibliotecas externas. O formato armazena também os caminhos absolutos 
   do diretório base e das stopwords, permitindo que a busca funcione mesmo 
   se o executável for rodado de outra pasta.

4. Processamento de Texto:
   O TextProcessor normaliza todas as palavras para minúsculas e remove pontuações.
   A verificação de stopwords é feita com 'std::unordered_set' para velocidade máxima.

NOTAS ADICIONAIS
---------------------------------------------------------------------------
O arquivo 'index.dat' é gerado na mesma pasta do executável. Se este arquivo
for corrompido ou apagado, é necessário rodar o comando 'construir' novamente.
# Trabalho-Pratico-3---Ordenacao-de-Anagramas-e-Tabela-Hash-
O objetivo é desenvolver um programa em C que encontre e agrupe palavras que são anagramas entre si dentro de um arquivo de texto, utilizando uma tabela hash.  Um anagrama é uma palavra formada pelas mesmas letras de outra, apenas reorganizadas.

Trabalho prático 3

Um anagrama é uma permutação das letras que compõem uma palavra. Por exemplo, R-O-M-A é um anagrama de A-M-O-R, assim como B-O-L-A é um anagrama de L-O-B-A. Detectar quais palavras são anagramas entre si pode se tornar uma tarefa complicada se não forem escolhidas estruturas de dados e métodos adequados. Por exemplo, uma abordagem que compara cada palavra com todas as outras terá complexidade quadrática, O(n^2), em relação ao número de palavras (assumindo custo constante por comparação, dependente do tamanho médio das palavras). Entretanto, uma abordagem que utiliza tabelas hash pode ser linear, O(n), em relação ao número de palavras. E é justamente essa abordagem que iremos conhecer e implementar neste trabalho.

Anagramas

Como mencionado anteriormente, anagramas são permutações das letras que compõem uma palavra. Nem todas as permutações têm de fazer sentido no idioma original. Por exemplo, O-A-R-M é um anagrama de A-M-O-R, embora não faça sentido em português. Uma relevante propriedade de anagramas é a ordenação, apresentada a seguir:

Ordenação: Como anagramas são permutações de elementos idênticos, a ordenação de dois anagramas resultará necessariamente na mesma sequência de caracteres. Por exemplo: ordenando em ordem alfabética, L-O-B-A e B-O-L-A (que são anagramas entre si) resultam ambos em A-B-L-O.

Tabela Hash

Utilizaremos uma tabela hash para detectar anagramas. Cada entrada da tabela será uma lista encadeada que armazenará todas as palavras que são anagramas entre si.  Devido à propriedade de ordenação mencionada anteriormente, o resultado dessa ordenação naturalmente se qualifica como uma chave potencial da tabela. Portanto, resta apenas a necessidade de criar uma função que converta essa string em um valor numérico. Entretanto, ao realizar essa transformação numérica, eventuais colisões podem ocorrer e, portanto, deve-se adotar uma estratégia para lidar com esse problema. Você pode escolher a estratégia que quiser, apenas lembre-se de justificar sua escolha e explicar seu funcionamento no relatório.

Detalhes de implementação

Você deverá implementar um Tipo Abstrato de Dados (TAD) TabelaHash. Além disso, como cada entrada da tabela é uma lista encadeada, será necessário implementar também um TAD Lista. Quanto ao tamanho da tabela, observe que o pior caso ocorre quando não há anagramas. Portanto, cada entrada na tabela será uma palavra isolada. Como a quantidade de palavras a serem analisadas é determinada em tempo de execução, a tabela hash deverá ser alocada dinamicamente. Por fim, para os processos de ordenação, você deverá obrigatoriamente utilizar um método de ordenação de tempo linear à sua escolha (por exemplo, Counting, Radix ou Bucket).

Entrada do programa

O programa receberá, através da linha de chamada, o caminho para o arquivo a ser testado:

./anagrama texto.txt

O arquivo será um texto de tamanho variável a ser analisado pelo programa. Será necessário ler e pré-processar este arquivo. Mais especificamente:
Todos os caracteres devem assumir forma minúscula;
Caracteres diferentes  de a-z devem ser removidos, por exemplo, acentos e cedilha (ç). 
Desta forma, ao final, o texto será composto apenas por palavras e espaços em branco para separá-las. Por exemplo:
        Yesterday I went to the movies. I liked it a lot, and I also ate a lot of popcorn.
se tornará
        yesterday i went to the movies i liked it a lot, and i also ate a lot of popcorn

Saída do programa

O programa deverá imprimir a “palavra ordenada” e os anagramas dela encontrados no texto. Os anagramas devem ser apresentados, sem repetição, na mesma ordem em que apareceram no texto. Cada uma das “palavras ordenadas” (junto com seus anagramas) deve ser apresentada em ordem alfabética. Exemplo:

ENTRADA: Listen closely: you must be silent. Also, listen to their conversation about conservation.

SAÍDA:  aceinnoorstv: conversation conservation
       eilnst: listen silent

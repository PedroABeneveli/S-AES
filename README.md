# S-AES e AES com Modos de Operação
Trabalho 2 da disciplina de Segurança Computacional do semestre 2025.1

## Aluno
- Pedro Avila Beneveli

## S-AES
Implementação do algoritmo S-AES, uma versão simplificada do algoritmo AES desenvolvida para fins educacionais. Além disso, foi implementado o modo de operação ECB para cifrar mensagens com tamanho maior que 16 bits.

### Compilação

Para compilar, basta executar a linha de comando abaixo no terminal no diretório ```S-AES/```:

```
make
```

Isso irá gerar o arquivo executável _saes_, que executa uma interface no terminal para criptografar mensagens com o S-AES ou com o Modo de Operação ECB.

### Como utilizar

É necessário apenas digitar no terminal, após realizar a compilação:

```
./saes
```

Com isso, instruções com as operações possíveis e os dados necessários para realizá-las serão mostradas no terminal.

## AES com Modos de Operação

Presente no diretório ```"AES Modes"/```, esses códigos têm o propósito de analisar o funcionamento dos modos de operação utilizando o AES, e também medir o tempo de cada um. Os modos de operação analisados são:

- Electronic Codebook (ECB)
- Cipher Block Chaining (CBC)
- Cipher Feedback (CFB)
- Output Feedback (OFB)
- Counter (CTR)

Essa parte do projeto foi desenvolvida em Python, para permitir o uso da biblioteca PyCryptodome.

### Setup

Para executar os códigos, é necessário instalar a biblioteca PyCryptodome, que é feito a partir do seguinte comando no terminal:

```
pip install pycryptodome
```

### Como utilizar

Para encriptar uma mensagem arbitrária com um modo de operação x (ecb, cbc, cfb, ofb ou ctr), deve-se executar o arquivo correspondente:

```
python3 x.py
```

A qual retornará o tempo necessário para realizar aquela cifra, além da opção de visualizar o texto cifrado em base64.

Além disso, para executar com uma das mensagens disponibilizadas, é necessário executar:

```
python3 x.py < plain_text_small.txt
```

Para o texto menor, que mostrará o texto cifrado também, ou:

```
python3 x.py < plain_text_big.txt
```

Para o texto maior, que melhor compara o tempo de execução entre os modos, mas não exibe o texto cifrado devido a sua grande extensão (2160000 caracteres do texto em claro).
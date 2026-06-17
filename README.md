# Jogo de Adivinhacao — PIF 2026.1

**Disciplina:** Programacao Imperativa e Funcional
**Instituicao:** CESAR School

## Equipe

| Nome | GitHub |
|---|---|
| Gustavo Rafael Renaux Veloso | (dono do repositorio) |
| Jardel Simplicio De Oliveira | — |
| Caio Gilles Costa Medeiros de Souza | [@CaioGilles](https://github.com/CaioGilles) |
| Eliziane Mota de Souza | [@Lizimota](https://github.com/Lizimota) |
| Luiz Felipe Matias Xavier | [@LuizMXavier](https://github.com/LuizMXavier) |
| Lucca Barbosa Spinelli | — |

---

## Sobre o Projeto

Jogo de adivinhacao em linguagem C: o programa sorteia um numero inteiro entre 1 e 100 e o jogador tenta acerta-lo recebendo dicas de "muito baixo" ou "muito alto" a cada palpite. Ao final de cada partida os dados sao persistidos em `historico.txt` e o modulo de analise exibe estatisticas agregadas de todas as sessoes.

---

## Como Compilar e Executar

### Pre-requisito
GCC ou MSVC (cl.exe) instalado e no PATH.

### GCC
```bash
cd adivinhacao
gcc main.c game.c stats.c io.c -o jogo -lm
./jogo          # Linux/macOS
jogo.exe        # Windows CMD
```

### MSVC (Visual Studio)
Abra o terminal do Developer Command Prompt dentro de `adivinhacao/` e pressione **Ctrl+Shift+B** no VS Code (tarefa "Build: Jogo"), ou execute:
```cmd
cl.exe /Zi /EHsc /nologo /Fejogo.exe main.c game.c stats.c io.c
jogo.exe
```

### Gerador de Testes (105 sessoes)
```bash
gcc test_gen.c -o test_gen
./test_gen
```
Ou pelo VS Code: tarefa **"Build: Gerador de Testes"** e entao `test_gen.exe`.

---

## Estrutura de Arquivos

```
adivinhacao/
  main.c        — ponto de entrada; menu principal
  game.h        — struct Session e prototipos do modulo de jogo
  game.c        — RNG e logica da partida (game_new_session)
  io.h          — prototipos das funcoes de persistencia
  io.c          — leitura e escrita de historico.txt
  stats.h       — prototipos das funcoes estatisticas
  stats.c       — funcoes recursivas de estatistica
  test_gen.c    — gerador automatico de 105 sessoes para testes
  historico.txt — base de dados das partidas (CSV)
```

---

## Especificacao dos Modulos

### game.h / game.c

#### Constante
| Nome | Valor | Descricao |
|---|---|---|
| `MAX_GUESSES` | 100 | Limite de palpites por partida |

#### Struct `Session`
```c
typedef struct {
    char timestamp[20];        // "AAAA-MM-DD HH:MM:SS"
    int  secret;               // numero sorteado (1..100)
    int  total_attempts;       // total de palpites realizados
    int  bias_low;             // palpites abaixo do segredo
    int  bias_high;            // palpites acima do segredo
    int  guesses_list[100];    // sequencia de palpites
} Session;
```
Invariante: `bias_low + bias_high == total_attempts - 1` (o ultimo palpite e sempre o acerto).

#### Funcoes
| Assinatura | Descricao |
|---|---|
| `void rng_init(void)` | Inicializa o gerador com `srand(time(NULL))` |
| `int rng_generate(int min, int max)` | Retorna inteiro aleatorio em `[min, max]` |
| `Session game_new_session(void)` | Executa uma partida interativa e retorna a sessao preenchida |

---

### io.h / io.c

#### Funcoes
| Assinatura | Descricao |
|---|---|
| `void history_save(Session s)` | Acrescenta a sessao em `historico.txt` (modo append) |
| `void history_load_and_print(void)` | Le o historico, imprime cada partida com heuristica e exibe estatisticas agregadas |

#### Formato de `historico.txt`
Cada linha representa uma partida:
```
timestamp;segredo;total;bias_low;bias_high;p1,p2,...,pN
```
Exemplo:
```
2026-01-10 08:00:00;73;7;3;3;50,75,62,68,71,72,73
```

---

### stats.h / stats.c

Todas as funcoes de agregacao sao implementadas **recursivamente**.

#### Funcoes
| Assinatura | Descricao | Complexidade |
|---|---|---|
| `int soma_recursiva(int v[], int n)` | Soma dos elementos | O(n) |
| `int min_recursivo(int v[], int n)` | Minimo (melhor partida) | O(n) |
| `int max_recursivo(int v[], int n)` | Maximo (pior partida) | O(n) |
| `long soma_quadrados_recursiva(int v[], int n)` | Soma dos quadrados (base para desvio padrao) | O(n) |
| `float desvio_padrao(int v[], int n)` | Desvio padrao usando `Var = E[X²] - (E[X])²` | O(n) |
| `const char* obter_heuristica(int tentativas)` | Retorna texto de feedback baseado no numero de tentativas | O(1) |

#### Heuristica de desempenho
| Tentativas | Feedback |
|---|---|
| <= 4 | Excelente — otima estrategia de busca |
| 5 a 7 | Bom — pode melhorar a reducao do intervalo |
| >= 8 | Dica de busca binaria |

A busca binaria otima resolve qualquer numero entre 1 e 100 em no maximo **7 tentativas** (ceil(log2(100)) = 7).

---

## Capstones Implementados

| Capstone | Entrega | Status |
|---|---|---|
| 1 | RNG, loop do jogo, menu, persistencia basica | Concluido |
| 2 | Funcoes recursivas (soma, min, max) e heuristica | Concluido |
| 3 | Refatoracao final, headers corretos, desvio padrao, 105 sessoes de teste, README | Concluido |

---

## Testes

O arquivo `test_gen.c` simula 105 partidas usando busca binaria com 20% de chance de palpite aleatorio (semente fixa 42 para reproducibilidade). O resultado e gravado em `historico.txt` e pode ser analisado pela opcao 2 do menu principal.

Apos gerar os testes, a saida esperada do relatorio incluira:
- **Media**: aprox. 6 tentativas
- **Desvio padrao**: aprox. 1.4
- **Melhor partida**: 3 tentativas
- **Pior partida**: 9 tentativas

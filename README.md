# Projeto: Jogo de Adivinhação (RNG)
**Disciplina:** Programação Imperativa e Funcional  
**Instituição:** CESAR School

## 👥 Equipe
* **Gustavo Rafael Renaux Veloso** (Dono do Repositório)
* **Jardel Simplicio De Oliveira**
* **Caio Gilles Costa Medeiros de Souza** — [GitHub](https://github.com/CaioGilles)
* **Eliziane Mota de Souza**
* **Luiz Felipe Matias Xavier** — [GitHub](https://github.com/LuizMXavier)
* **Lucca Barbosa Spinelli**

## 📝 Sobre o Projeto
Este repositório contém a implementação de um jogo de adivinhação desenvolvido em linguagem C. O projeto utiliza uma estrutura modular (arquivos `.c` e `.h`) e um sistema de geração de números aleatórios (RNG) para definir o número secreto a cada sessão.

## 🚀 Como Compilar e Executar
Para rodar o projeto localmente, certifique-se de ter o compilador `gcc` instalado.

1. **Abra o terminal** na pasta do projeto.
2. **Compile os arquivos:**
   ```bash
   gcc main.c game.c stats.c io.c -o jogo.exe
    ```
- No Linux/macOS/Git Bash:
    `./jogo.exe`

- No Windows (CMD):
    `jogo.exe`

## 🛠️ Estrutura de Arquivos
- main.c: Ponto de entrada do programa.

- game.c / game.h: Lógica do jogo e geração do número aleatório.

- stats.c / stats.h: (Em desenvolvimento) Gestão de estatísticas.

- io.c / io.h: (Em desenvolvimento) Funções de entrada e saída.

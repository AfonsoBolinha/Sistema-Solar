# Como usar
## Compilação e execução
1. Fazer download dos ficheiros e colocar numa pasta
2. Abrir o WSL e navegar até a pasta
3. Executar o comando ```g++ main.cpp glad/src/glad.c objloader.cpp -o rotating -I/usr/include/freetype2 -lglfw -lGLEW -lGL -lX11 -lpthread -lXrandr -ldl -lfreetype``` (⚠️ **Pode ser necessário instalar bibliotecas no WSL**)
4. Executar o programa com o comando ```./rotating```

## Interação
- Rotação dos planetas para um sentido ou para o outro **-** **Seta Esquerda** e **Seta Direita**
- Rotação dos planetas para um sentido ou para o outro **-** **Seta Esquerda** e **Seta Direita**
- Aceleração da rotação dos planetas e desaceleração **-** **E** e **Q**
- Movimentação espacial para a frente e para trás **-** **W** e **S**
- Movimentação espacial para a direita e para a esquerda **-** **D** e **A**
- Olhar em redor **-** **Rato**
- Obter informação de um planeta (só é possível quando extremamente próximo do mesmo) **-** **Tecla Esquerda do Rato**

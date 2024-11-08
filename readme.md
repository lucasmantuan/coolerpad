# Coolerpad

Mini projeto que implementa coolerpad para notebooks utilizando Armbian e Cubieboard, com controle dinâmico de potência do cooler de acordo com a temperatura medida. A velocidade é ajustada automaticamente com base em intervalos predefinidos.

### Funcionalidades
- Leitura de Temperatura: Acessa o arquivo do sensor para obter a temperatura, valida os dados e converte o valor para graus Celsius.
- Acionamento do Ventilador: Controla o funcionamento do ventilador, ligando ou desligando conforme a temperatura detectada.
- Controle de Velocidade: Ajusta a velocidade do ventilador através de controle PWM (Pulse Width Modulation).

### Configurações
- Para utilizar um pino GPIO no Armbian/Cubieboard, identifique o pino e execute echo `PIN > /sys/class/gpio/export` para liberar a porta. Configure os arquivos `direction` e `value` para ajustar o comportamento do pino.
- Para ativar a porta PWM, execute `echo 0 > /sys/class/pwm/pwmchip0/export` e configure os arquivos `enable`, `period` e `duty_cycle` dentro da pasta PWM.
- Para configurar o dispositivo One Wire, adicione as seguintes linhas ao arquivo `/boot/armbianEnv.txt`, especificando o pino GPIO:

```
overlays=w1-gpio 
param_w1_pin=PIN
param_w1_pin_int_pullup=0
```

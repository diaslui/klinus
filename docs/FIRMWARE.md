# Firmware

Olá! Nesta seção, você encontrará informações sobre os firmwares utilizados neste projeto.

## Divisão de Dispositivos

O projeto está dividido em dois dispositivos principais:

1. **Dispositivo Rádio**: responsável por manter comunicação com o servidor externo e detectar a presença de pessoas na sala por meio de sensores de movimento. Também se comunica com o Dispositivo Head para solicitar que comandos sejam enviados ao ar-condicionado.

    **Localização geográfica (rádio)**: este dispositivo deve estar em um local com boa visibilidade da sala (recomenda-se o centro) para garantir a detecção de movimento, além de boa recepção de sinal Wi-Fi para garantir a comunicação com o servidor externo.

    **Componentes (rádio)**:
    - ESP32 C3 MINI
    - Sensor LD2410 (Detector de presença)

2. **Dispositivo Head**: responsável por receber os pedidos do Dispositivo Rádio e transmiti-los via sinais infravermelhos ao ar-condicionado.

    **Localização geográfica (Head)**: este dispositivo deve ficar o mais próximo possível do ar-condicionado, em linha de visão direta, para garantir que os sinais infravermelhos sejam recebidos corretamente.

    **Componentes (Head)**:
    - ESP32 C3 MINI
    - IR Transmitter (Transmissor Infravermelho)


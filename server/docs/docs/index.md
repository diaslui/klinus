# Klinus

O Klinus é um sistema de automação desenvolvido para otimizar o uso de ar-condicionado em instituições públicas, visando a redução do consumo energético e promovendo a sustentabilidade ambiental. Utilizando sensores de presença e comunicação sem fio, o sistema ajusta automaticamente o funcionamento dos aparelhos de ar-condicionado com base na ocupação dos ambientes.

## Tecnologias Utilizadas

### Hardware

- **Microcontroladores ESP32 C3 MINI**: Utilizados para controlar os dispositivos de rádio e head, permitindo a comunicação via Wi-Fi e o envio de sinais infravermelhos.
- **Sensor LD2410**: Sensor de presença utilizado para detectar a ocupação dos ambientes.
- **Transmissor Infravermelho**: Componente responsável por enviar comandos ao ar-condicionado.

### Software
- **Firmware em C/C++**: Desenvolvido para os microcontroladores ESP32, gerenciando a lógica de detecção de presença e controle do ar-condicionado.
- **Servidor Django (Backend)**: Responsável por gerenciar a comunicação entre os dispositivos e armazenar dados de uso e desempenho.


## Contribuição

- Fork → feature branch → pull request com descrição e testes.
- Siga padrões de formatação (flake8/black) e escreva testes básicos para alterações de backend.

## Próximos passos

- [Servidor](server/instalacao.md) — instruções para instalar o servidor.
- [Firmware](firmware/dispositivos.md) — sobre os dispositivos e firmware.

## Licença
Este projeto está licenciado sob a Licença MIT. Veja o arquivo [LICENSE](../../LICENSE) para mais detalhes.
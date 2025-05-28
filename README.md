# Sistema de Monitoramento e Reúso de Água com MQTT
Sistema de Monitoramento de Consumo de Água Doméstica com Reuso para Sustentabilidade

Este projeto consiste em um Sistema de Monitoramento e Reúso de Água Doméstica, utilizando sensores para medir o consumo e o nível de um reservatório, com automação no acionamento de uma bomba submersa e comunicação via protocolo MQTT. O sistema visa otimizar o uso consciente da água, destinando a água reutilizada para atividades não potáveis, como descargas sanitárias.
Os dados coletados são transmitidos em tempo real para uma plataforma remota através de MQTT, permitindo o monitoramento e controle à distância.


Funcionamento

Medição de Vazão: Sensor de fluxo calcula o volume de água utilizada.
Medição de Nível: Sensor ultrassônico detecta a altura do reservatório, identificando quando o nível está baixo.
Automação: Quando o nível atinge o valor mínimo configurado, o sistema aciona automaticamente a bomba submersa via relé.
Comunicação: Todos os dados são enviados via MQTT para um broker configurado, podendo ser acessados por aplicativos ou dashboards de monitoramento.
Interface: O Arduino realiza a coleta e processamento dos dados; o envio MQTT é feito por um notebook ou Raspberry Pi, atuando como gateway serial-MQTT.

Hardware Utilizado

- Microcontrolador
Arduino Uno R3 (ATmega328 SMD)
Plataforma responsável pela aquisição de dados e controle dos atuadores.

- Sensores
Sensor de Fluxo Hall YF-S201
Capacidade: até 30 L/min.
Utilizado para medir o volume de água que passa pelo sistema.

Sensor Ultrassônico HC-SR04
Faixa de medição: 2 cm a 400 cm.
Utilizado para medir a altura da água no reservatório.

- Atuadores
Mini Bomba Submersa JT100 5V DC
Vazão: 120 L/h.
Acionada automaticamente para realimentar o reservatório de água de reúso.

Módulo Relé 1 Canal 5V
Utilizado para controlar o acionamento da bomba de forma segura e isolada eletricamente

Protoboard de 830 pontos
Montagem sem solda para facilitar o desenvolvimento e ajustes.

Jumpers Macho/Fêmea (20 cm)
Facilita a interligação dos componentes.

Fonte 5V 2A Bivolt
Alimenta o Arduino e a bomba de forma estável.

Notebook
Atua como interface entre o Arduino e o broker MQTT.
Software: Python com bibliotecas pyserial e paho-mqtt



# ledCube4-4-4
Код и полезная информация по светодиодному кубу 4х4х4

Статья по созданию куба:http://cxem.net/sound/light/light44.php

Прерывания INTx в Atmega8, для Atmega16 подходит тоже: http://mainloop.ru/avr-atmega/avr-external-interrupt.html

Микроконтроллер Atmega16, код для Atmel Studio 6

Баги:
1. После обработки прерывания, программа возвращается и доделывает старый эффект, хотя, по идее, уже должна начинать новый. Надо как-то запускать цикл while сначала

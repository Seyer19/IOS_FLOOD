# IOS_FLOOD
IOS Notification flooding
# iOS Notification Flood via BLE (ESP32 + nRF24)

## Concepto

Inundar un dispositivo iOS 17+ con notificaciones de "nueva conexión" simulando la aparición de múltiples dispositivos Bluetooth Low Energy (BLE): audífonos, Apple Watch, llaveros AirTag, etc.

**Nota:**
 Esto no es una vulnerabilidad de seguridad real, sino una técnica de acoso/interferencia que abusa del comportamiento normal de iOS al detectar nuevos dispositivos BLE cercanos.

## ¿Cómo funciona?

iOS muestra notificaciones cuando detecta:
- Dispositivos Bluetooth emparejados que se reconectan
- Nuevos dispositivos AirTag cerca
- Apple Watch que se conecta/desconecta
- Accesorios MFi (Made for iPhone)

Al transmitir anuncios BLE con UUIDs específicos de estos dispositivos, podemos engañar a iOS para que muestre notificaciones.

## Componentes necesarios

### Hardware
| Componente | Cantidad | Precio aprox. |
|------------|----------|---------------|
| ESP32 DevKit (con WiFi y BLE) | 1 | $5-8 USD |
| Módulo nRF24L01+ (opcional, para rango extendido) | 1 | $2-3 USD |
| Cables USB-C | 1 | - |
| Batería LiPo 3.7V (opcional) | 1 | $5-8 USD |

### Software
- Arduino IDE o PlatformIO
- Biblioteca `BLEDevice` (incluida en ESP32 core)
- Biblioteca `nRF24` (si se usa nRF24L01+)

## Pines necesarios (ESP32)

| Pin ESP32 | Función | Conexión |
|-----------|---------|----------|
| GPIO 16 | SPI MOSI | nRF24 MOSI |
| GPIO 17 | SPI MISO | nRF24 MISO |
| GPIO 5 | SPI SCK | nRF24 SCK |
| GPIO 4 | CSN | nRF24 CE |
| GPIO 2 | IRQ | nRF24 IRQ |
| GPIO 33 | LED indicador | LED + resistor |

## Scripts incluidos

1. `esp32_ble_flood.ino` - Script principal para ESP32 que transmite anuncios BLE
2. `nrf24_extended_range.cpp` - Versión con nRF24L01+ para mayor alcance
3. `config.json` - Configuración de dispositivos a simular

## Instrucciones de uso

### 1. Configurar Arduino IDE
- Instalar ESP32 board package
- Instalar bibliotecas BLE y nRF24

### 2. Compilar y subir
```bash
# Con PlatformIO
pio run -t upload
```

### 3. Ejecutar el ataque
El dispositivo comenzará a transmitir anuncios BLE cada 100ms con diferentes UUIDs simulando:
- AirPods (UUID: E0B9A5D8-F67C-4F2E-A3B1-D4E5F6A7B8C9)
- Apple Watch (UUID: A495BB20-C5B1-4B44-B512-1370F6AE8C4D)
- AirTag (UUID: 0x004C0002)

## Limitaciones

- iOS puede ignorar anuncios repetidos del mismo dispositivo
- La distancia efectiva es limitada (~10m sin nRF24)
- No funciona con iOS en modo "No molestar"
- Requiere que el BLE esté habilitado en el iPhone

## Referencias técnicas

- [ESP32 BLE Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/bluetooth.html)
- [nRF24L01+ Datasheet](https://www.nordicsemi.com/-/media/Products/Short-range-wireless/nRF24L01P/documents/ProductSpec/nRF24L01P_Product_Specification_Rev3.pdf)
- [iOS BLE Notification Behavior](https://developer.apple.com/documentation/corebluetooth)

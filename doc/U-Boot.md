# Das U-Boot

U-Boot står för universal boot loader, och är ett bootsystem som finns portat
till ett flertal system. Det kon boota från i stort sett allt.

# Konfiguration

## boot.scr

Skript som körs vid boot. I konstigt format.

Generera från råtext med kommandot mkimage.

Paketet u-boot-tools (Debian) innehåller programmet.

## uEnv.txt

Variabler som sätts vid boot.

# Bootmöjligheter

(Av någon anledning kan jag bara boota ELF-filer, inte img. Undersök!)

## Minneskort

 U-Boot> fatload mmc 0:1 ${loadaddr} kernel.img

## USB

## Ethernet

U-Boot kan även boota över Ethernet, om närverket är konfigurerat för detta.
Nätverksboot kräver att man först startar USB (då närverkschippet är anslutet
via USB)

 U-Boot> usb start

Genom att sedan skriva

 U-Boot> dhcp

Frågar U-Boot själv efter IP-address och laddar in den av servern angivna
filen från den av servern angivna tftp-servern.

Konfiguration, såsom fast IP, anges genom variabler och kan specificeras i
uEnv.txt

Booten kan även göras manuellt genom att sätta statiskt IP och sedan köra
typ tftpboot(?).

## Terminal

Kan även boota genom att ladda in S-records från terminalen. Konvertera
till S-records såhär.

 srec_cat kernel.img -binary -o rtos.srec && echo S9030000FC >> rtos.srec

# Övriga funktioner

Memory display, memory modify.

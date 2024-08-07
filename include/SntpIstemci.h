#ifndef __SntpIstemci__H__
#define __SntpIstemci__H__

bool SntpIstemci_SaatDogruMu();
void SntpIstemci_Baslat();
bool SntpIstemci_Yazdir(char* Tampon, uint32_t Adet);
String SntpIstemci_Yazdir();
int8_t SntpIstemci_HaftaninGunu();
uint16_t SntpIstemci_SaatDakika();

#endif
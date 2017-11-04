// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#include <libnet/mac.h>

void libnet_mac_init(struct libnet_mac *mac)
{
	for (unsigned int i = 0; i < 6; i++)
		mac->octets[i] = 0;
}

int libnet_mac_parse(struct libnet_mac *mac,
                     const char *str,
                     unsigned long long int len)
{
	unsigned long long int octets_found = 0;

	unsigned long long int i = 0;

	for (;;)
	{
		if (i >= len)
			break;

		unsigned octet = 0;

		char c = str[i];
		if ((c >= 'a') && (c <= 'f'))
			octet += (unsigned char) ((c - 'a') + 10);
		else if ((c >= 'A') && (c <= 'F'))
			octet += (unsigned char) ((c - 'A') + 10);
		else if ((c >= '0') && (c <= '9'))
			octet += (unsigned char) (c - '0');
		else
			break;

		octet <<= 4;
		i++;

		if (i >= len)
			break;

		c = str[i];
		if ((c >= 'a') && (c <= 'f'))
			octet += (unsigned char) ((c - 'a') + 10);
		else if ((c >= 'A') && (c <= 'F'))
			octet += (unsigned char) ((c - 'A') + 10);
		else if ((c >= '0') && (c <= '9'))
			octet += (unsigned char) (c - '0');
		else
			break;

		mac->octets[octets_found] = octet;
		octets_found++;
		i++;

		if ((i >= len) || (octets_found >= 6))
			break;

		if ((str[i] == '-')
		 || (str[i] == ':'))
			i++;
	}

	if (octets_found != 6)
		return -1;

	return 0;
}

int libnet_mac_write(const struct libnet_mac *mac,
                     char *str,
                     unsigned long long int len)
{
	if (len < 18)
		return -1;

	unsigned int j = 0;

	const char hexchars[] = "0123456789abcdef";

	for (unsigned int i = 0; i < 6; i++)
	{
		str[j++] = hexchars[(mac->octets[i] & 0xf0) >> 4];
		str[j++] = hexchars[(mac->octets[i] & 0x0f) >> 0];
		if ((i + 1) >= 6)
			str[j] = 0;
		else
			str[j++] = '-';
	}

	return 0;
}

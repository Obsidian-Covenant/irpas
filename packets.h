/* IRPAS project - packet library
 *
 * FX <fx@phenoelit.de>
 * Phenoelit (http://www.phenoelit.de)
 * (c) 2k
 *
 * $Id: packets.h,v 1.2 2001/06/16 18:17:31 fx Exp $
 */

#ifndef _PACKET_H_
#define _PACKET_H_

#include <stdint.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <netinet/in.h>


typedef struct {
        /* Ethernet address of the interface */
        struct ether_addr	eth;
	/* IPv4 address of the interface */
	struct in_addr		ip;
	struct in_addr		bcast;
	/* Maximum transfer unit for this interface */
	unsigned int		mtu;
} packet_ifconfig_t;


extern packet_ifconfig_t	 packet_ifconfig;


void    	*smalloc(size_t size);

/* network init */
int     	init_socket_eth(char *device);
int     	init_socket_IP4(char *device, int broadcast);

/* network sending */
int     	sendpack_IP4(int sfd, uint8_t *packet,int plength);
int     	sendpack_eth(char *device, int atsock,
			uint8_t *frame, int frame_length);

/* checksum */
uint16_t 	chksum(uint8_t *data, unsigned long count);

/* ping */
int     	icmp_ping(struct in_addr *t,int timeout,int verbose);
void		makenonblock(int s);
int		makebcast(int s);

#endif /*_PACKET_H_*/

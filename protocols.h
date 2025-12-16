/* Phenoelit IRPAS 
 * protocol definitions
 *
 * $Id: protocols.h,v 1.9 2001/10/18 12:02:58 fx Exp $
 */
#ifndef _PROTOCOLS_H_
#define _PROTOCOLS_H_

#include <stdint.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <netinet/in.h>

/* ************************************************************
 * Ethernet Frames
 * ************************************************************/
typedef struct {
    struct ether_addr   daddr;
    struct ether_addr   saddr;
    uint16_t           type;
} etherIIhdr_t;

/* IEEE 802.3, LLC related structs */
struct eth_ieee802_3 {
    struct ether_addr   daddr;
    struct ether_addr   saddr;
    uint16_t           length;
};

struct eth_LLC {
    uint8_t            DSAP;
    uint8_t            SSAP;
    uint8_t            Control;
    uint8_t            orgcode[3];
    uint16_t           proto;
};

struct eth_LLC_short {
    uint8_t            DSAP;
    uint8_t            SSAP;
    uint8_t            Control;
    uint8_t            orgcode[3];
    uint16_t           proto;
};

/* ************************************************************
 * CDP frames
 * ************************************************************/

/* CDP header */
struct cdphdr {
    uint8_t            version;
    uint8_t            ttl;
    uint16_t           checksum;
};
/* CDP sections */
#define TYPE_DEVICE_ID          0x0001
#define TYPE_ADDRESS            0x0002
#define TYPE_PORT_ID            0x0003
#define TYPE_CAPABILITIES       0x0004
#define TYPE_IOS_VERSION        0x0005
#define TYPE_PLATFORM           0x0006
#define TYPE_VTP_MGMT		0x0009
#define TYPE_VLAN		0x000a
#define TYPE_DUPLEX		0x000b

struct cdp_device {
    uint16_t           type;           /* 0x0001 */
    uint16_t           length;
    uint8_t              device;         /* pointer to device name */
};

struct cdp_address {
    uint16_t           type;           /* 0x0002 */
    uint16_t           length;
    uint32_t           number;         /* number of addresses */
};

struct cdp_address_entry {
    uint8_t            proto_type;     /* 0x1 for NLPID */
    uint8_t            length;         /* 0x1 for IP */
    uint8_t            proto;          /* 0xCC for IP */
    uint8_t            addrlen[2];
    uint8_t              addr;
};

struct cdp_port {
    uint16_t           type;           /* 0x0003 */
    uint16_t           length;
    uint8_t              port;           /* pointer to port name */
};


#define CDP_CAP_LEVEL1          0x40
#define CDP_CAP_FORWARD_IGMP    0x20
#define CDP_CAP_NETWORK_LAYER   0x10
#define CDP_CAP_LEVEL2_SWITCH   0x08
#define CDP_CAP_LEVEL2_SRB      0x04
#define CDP_CAP_LEVEL2_TRBR     0x02
#define CDP_CAP_LEVEL3_ROUTER   0x01
struct cdp_capabilities {
    uint16_t           type;           /* 0x0004 */
    uint16_t           length;         /* is 8 */
    uint32_t           capab;
};

struct cdp_software {
    uint16_t           type;           /* 0x0005 */
    uint16_t           length;
    uint8_t              software;       /* pointer to software string */
};

struct cdp_platform {
    uint16_t           type;           /* 0x0006 */
    uint16_t           length;
    uint8_t              platform;       /* pointer to platform string */
};

typedef struct {
    uint16_t           type;           
    uint16_t           length;
    uint8_t              value;           /* pointer to port name */
} cdp_generic_t;

/* ************************************************************
 * PPPoE 
 * ************************************************************/
typedef struct __attribute__((packed)) {
    uint8_t		version:4,type:4;
    uint8_t		code;
    uint16_t           session;
    uint16_t           payload_len;
} pppoe_data_t;


/* ************************************************************
 * ARP version 4
 * ************************************************************/
#define ARPOP_REQUEST   1               /* ARP request.  */
#define ARPOP_REPLY     2               /* ARP reply.  */
#define ARPOP_RREQUEST  3               /* RARP request.  */
#define ARPOP_RREPLY    4               /* RARP reply.  */
typedef struct {
    uint16_t	hardware;
    uint16_t	protocol;
    uint8_t	hw_size;
    uint8_t	proto_size;
    uint16_t	opcode;
    uint8_t	sha[ETH_ALEN];   	/* Sender hardware address.  */
    uint8_t 	sip[4];	          	/* Sender IP address.  */
    uint8_t 	tha[ETH_ALEN];   	/* Target hardware address.  */
    uint8_t 	tip[4];          	/* Target IP address.  */
} arphdr_t;


/* ************************************************************
 * IP version 4
 * ************************************************************/
/*#define IPPROTO_ICMP	0x01*/
#define IPPROTO_IGRP    0x09
/*#define IPPROTO_UDP	0x11*/
#define IPPROTO_EIGRP	0x58
#define IPPROTO_OSPF	0x59
/*#define IPPROTO_GRE	0x2f*/

#define IP_ADDR_LEN	4
typedef struct {
        uint8_t        ihl:4,          /* header length */
                        version:4;      /* version */
        uint8_t        tos;            /* type of service */
        uint16_t       tot_len;        /* total length */
        uint16_t       id;             /* identification */
        uint16_t       off;            /* fragment offset field */
        uint8_t        ttl;            /* time to live */
        uint8_t        protocol;       /* protocol */
        uint16_t       check;          /* checksum */
        struct in_addr  saddr;
        struct in_addr  daddr;  	/* source and dest address */
} iphdr_t;

/* ************************************************************
 * TCP
 * ************************************************************/
typedef struct {
    uint16_t th_sport;         /* source port */
    uint16_t th_dport;         /* destination port */
    uint32_t th_seq;             /* sequence number */
    uint32_t th_ack;             /* acknowledgement number */
#if __BYTE_ORDER == __LITTLE_ENDIAN
    uint8_t th_x2:4;           /* (unused) */
    uint8_t th_off:4;          /* data offset */
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
    uint8_t th_off:4;          /* data offset */
    uint8_t th_x2:4;           /* (unused) */
#endif
    uint8_t th_flags;
#define TH_FIN  0x01
#define TH_SYN  0x02
#define TH_RST  0x04
#define TH_PUSH 0x08
#define TH_ACK  0x10
#define TH_URG  0x20
    uint16_t th_win;           /* window */
    uint16_t th_sum;           /* checksum */
    uint16_t th_urp;           /* urgent pointer */
} tcphdr_t;

struct pseudohdr {
    struct in_addr saddr;
    struct in_addr daddr;
    uint8_t zero;
    uint8_t protocol;
    u_short length;
    tcphdr_t tcpheader;
};

/* ************************************************************
 * UDP
 * ************************************************************/
typedef struct __attribute__((packed)) {
    uint16_t	sport;
    uint16_t	dport;
    uint16_t	length;
    uint16_t	checksum;
} udphdr_t;


/* ************************************************************
 * IGRP 
 * ************************************************************/
#define IGRP_OPCODE_REQUEST     2
#define IGRP_OPCODE_UPDATE      1

typedef struct __attribute__((packed)) {
    uint8_t            opcode:4,version:4;
    uint8_t            edition;
    uint16_t           autosys;
    uint16_t           interior;
    uint16_t           system;
    uint16_t           exterior;
    uint16_t           checksum;
} igrp_t;

/* 
 * comment:
 *      the thing with delay[3] ... is very ugly, but I'm not good 
 *      in representing this perhaps 3 byte long data type correctly.
 *      Cisco's documentation has still free space for improvements  ...
 */
typedef struct __attribute__((packed)) {
    uint8_t            destination[3];
    uint8_t            delay[3];
    uint8_t            bandwith[3];
    uint16_t           mtu;
    uint8_t            reliability;
    uint8_t            load;
    uint8_t            hopcount;
} igrp_system_entry_t;


/* ************************************************************
 * ICMP
 * ************************************************************/
#define ICMP_ECHOREPLY          0       /* Echo Reply                   */
#define ICMP_DEST_UNREACH       3       /* Destination Unreachable      */
#define ICMP_SOURCE_QUENCH      4       /* Source Quench                */
#define ICMP_REDIRECT           5       /* Redirect (change route)      */
#define ICMP_ECHO               8       /* Echo Request                 */
#define ICMP_ROUTER_ADVERT	9	/* router advertisement 	*/
#define ICMP_SOLICITATION	10	/* router solicitation		*/
#define ICMP_TIME_EXCEEDED      11      /* Time Exceeded                */
#define ICMP_PARAMETERPROB      12      /* Parameter Problem            */
#define ICMP_TIMESTAMP          13      /* Timestamp Request            */
#define ICMP_TIMESTAMPREPLY     14      /* Timestamp Reply              */
#define ICMP_INFO_REQUEST       15      /* Information Request          */
#define ICMP_INFO_REPLY         16      /* Information Reply            */
#define ICMP_ADDRESS            17      /* Address Mask Request         */
#define ICMP_ADDRESSREPLY       18      /* Address Mask Reply           */
/* Codes for REDIRECT. */
#define ICMP_REDIR_NET          0       /* Redirect Net                 */
#define ICMP_REDIR_HOST         1       /* Redirect Host                */
#define ICMP_REDIR_NETTOS       2       /* Redirect Net for TOS         */
#define ICMP_REDIR_HOSTTOS      3       /* Redirect Host for TOS        */
/* codes for unreach */
#define ICMP_UNREACH_NET	0
#define ICMP_UNREACH_HOST	1
#define ICMP_UNREACH_PROTO	2	/* protocol unreachable 	*/
#define ICMP_UNREACH_PORT	3	/* port unreachable 		*/
#define ICMP_UNREACH_FRAG	4	/* fragmentation needed and DF	*/
#define ICMP_UNREACH_SOURCE	5	/* source route failed 		*/
#define ICMP_UNREACH_ADMIN1	9	/* administratively prohibited	*/
#define ICMP_UNREACH_TOS	11	/* unreach fro TOS		*/
#define ICMP_UNREACH_FIREWALL	13	/* port filtered 		*/

typedef struct __attribute__((packed)) {
    uint8_t  type;
    uint8_t  code;
    uint16_t checksum;
} icmphdr_t;

typedef struct __attribute__((packed)) {
    uint16_t	identifier;
    uint16_t	seq;
    uint8_t	data[56];
} icmp_echohdr_t;

typedef struct __attribute__((packed)) {
    icmphdr_t		icmp;
    icmp_echohdr_t	echo;
} icmp_ping_t;

typedef struct __attribute__((packed)) {
    uint16_t	identifier;
    uint16_t	seq;
    uint8_t	mask[4];
} icmp_netmask_t;

typedef struct __attribute__((packed)) {
    uint16_t   identifier;
    uint16_t   seq;
    uint32_t   origts;
    uint32_t   recvts;
    uint32_t   transts;
} icmp_timestamp_t;

typedef struct __attribute__((packed)) {
    uint8_t	num_addr;
    socklen_t	addrsize;
    uint16_t	lifetime;
} irdp_t;

typedef struct __attribute__((packed)) {
    uint8_t	addr[4];
    uint32_t	pref;
} irdp_rec_t;

typedef struct __attribute__((packed)) {
    uint8_t	type;
    uint8_t	code;
    uint16_t	checksum;
    uint32_t	reserved;
} irdp_solicitation_t;

typedef struct __attribute__((packed)) {
    uint8_t	type;
    uint8_t	code;
    uint16_t	checksum;
    uint8_t	gateway[4];
    uint8_t	headerdata[28];
} icmp_redirect_t;

/* ************************************************************
 * OSPF
 * ************************************************************/
#define OSPF_HELLO      1
#define OSPF_DB_DESC    2
#define OSPF_LS_REQ     3
#define OSPF_LS_UPD     4
#define OSPF_LS_ACK     5

#define OSPF_AUTH_NONE          0
#define OSPF_AUTH_SIMPLE        1
#define OSPF_AUTH_CRYPT         2

typedef struct __attribute__((packed)) {
    uint8_t	version;
    uint8_t	type;
    uint16_t	length;
    uint8_t	source[4];
    uint8_t	area[4];
    uint16_t	checksum;
    uint16_t	authtype;
    uint8_t	authdata[8];
} ospf_header_t;

typedef struct __attribute__((packed)) {
    uint8_t	netmask[4];
    uint16_t	hello_interval;
    uint8_t	options;
    uint8_t	priority;
    uint8_t	dead_interval[4];
    uint8_t	designated[4];
    uint8_t	backup[4];
    //uint8_t	activeneig[4];
} ospf_hello_t;

/* ************************************************************
 * Spanning Tree (STP)
 * ************************************************************/

typedef struct __attribute__((packed)) {
    uint16_t	protocolid;
    uint8_t	version;
    uint8_t	BPDU_type;
    uint8_t	BPDU_flags;
    uint16_t	root_priority;
    uint8_t	root_id[6];
    uint8_t	root_path_cost[4];
    uint16_t	bridge_priority;
    uint8_t	bridge_id[6];
    uint16_t	port_id;
    uint16_t	message_age;
    uint16_t	max_age;
    uint16_t	hello_time;
    uint16_t	forward_delay;
} stp_t;

/* ************************************************************
 * EIGRP
 * ************************************************************/

#define EIGRP_UPDATE    0x01
#define EIGRP_REQUEST   0x02
#define EIGRP_QUERY     0x03
#define EIGRP_REPLY     0x04
#define EIGRP_HELLO     0x05

#define EIGRP_TYPE_PARA		0x0001
#define EIGRP_TYPE_SOFT		0x0004
#define EIGRP_TYPE_IN_ROUTE	0x0102
#define EIGRP_TYPE_EX_ROUTE	0x0103

typedef struct __attribute__((packed)) {
   uint8_t	version;
   uint8_t	opcode;
   uint16_t	checksum;
   uint32_t	flags;
   uint32_t	seq;
   uint32_t	ack;
   uint32_t	as;
} eigrp_t;

typedef struct __attribute__((packed)) {
    uint16_t	type;
    uint16_t	length;
    uint8_t	iosmaj;
    uint8_t	iosmin;
    uint8_t	eigrpmaj;
    uint8_t	eigrpmin;
} eigrpsoft_t;

typedef struct __attribute__((packed)) {
    uint16_t	type;
    uint16_t	length;
    uint8_t	k1;
    uint8_t	k2;
    uint8_t	k3;
    uint8_t	k4;
    uint8_t	k5;
    uint8_t	reseved;
    uint16_t	holdtime;
} eigrppara_t;

typedef struct __attribute__((packed)) {
    uint16_t	type;
    uint16_t	length;
    uint8_t	nexthop[4];
    uint8_t	origrouter[4];
    uint32_t	origas;
    uint32_t	tag;
    uint32_t	external_metric;
    uint16_t	reserved_1;
    uint8_t	external_link;
    uint8_t	flags;
    uint32_t	delay;
    uint32_t	bandwidth;
    uint8_t	mtu[3];
    uint8_t	hopcount;
    uint8_t	reliability;
    uint8_t	load;
    uint16_t	reserved_2;
    uint8_t	prefix_length;
    		/* Warning: 
		 * this filed is variable and depends on prefix_length 
		 * 8= 1
		 * 16=2
		 * 24=3
		 * 32=4*/
    uint8_t	dest;
} eigrpextroute_t;

typedef struct __attribute__((packed)) {
    uint16_t	type;
    uint16_t	length;
    uint8_t	nexthop[4];
    uint32_t	delay;
    uint32_t	bandwidth;
    uint8_t	mtu[3];
    uint8_t	hopcount;
    uint8_t	reliability;
    uint8_t	load;
    uint16_t	reserved_2;
    uint8_t	prefix_length;
    		/* Warning: 
		 * this filed is variable and depends on prefix_length 
		 * 8= 1
		 * 16=2
		 * 24=3
		 * 32=4*/
    uint8_t	dest;
} eigrpintroute_t;

/* ************************************************************
 * RIP v1
 * ************************************************************/
#define RIP_PORT		520
#define RIP_COMMAND_REQUEST	1
#define RIP_COMMAND_RESPONSE	2

typedef struct __attribute__((packed)) {
    uint8_t	command;
    uint8_t	version;
    uint16_t	zero;
} ripv1hdr_t;

typedef struct __attribute__((packed)) {
    uint16_t	addrfamily;
    uint16_t	zero1;
    uint8_t	address[4];
    uint16_t	zero2[4];
    uint32_t	metric;
} ripv1addr_t;

typedef struct __attribute__((packed)) {
    uint8_t	command;
    uint8_t	version;
    uint16_t	domain;
} ripv2hdr_t;

typedef struct __attribute__((packed)) {
    uint16_t	addrfamily;
    uint16_t	routetag;
    uint8_t	address[4];
    uint8_t	netmask[4];
    uint8_t	nexthop[4];
    uint32_t	metric;
} ripv2addr_t;

typedef struct __attribute__((packed)) {
    uint16_t	addrfamily;
    uint16_t	authtype;
    uint8_t	auth[16];
} ripv2auth_t;

/* ************************************************************
 * GRE
 * ************************************************************/
typedef struct {
    uint16_t	flags;
    uint16_t	proto;
} grehdr_t;

/* ************************************************************
 * HSRP
 * ************************************************************/
#define HSRP_OPCODE_HELLO  0
#define HSRP_OPCODE_COUP   1
#define HSRP_OPCODE_RESIGN 2

#define HSRP_STATE_INITIAL  0
#define HSRP_STATE_LEARN    1
#define HSRP_STATE_LISTEN   2
#define HSRP_STATE_SPEAK    4
#define HSRP_STATE_STANDBY  8
#define HSRP_STATE_ACTIVE  16

typedef struct {
    uint8_t	version;
    uint8_t	opcode;
    uint8_t	state;
    uint8_t	hellotime;
    uint8_t	holdtime;
    uint8_t	prio;
    uint8_t	group;
    uint8_t	reserved;
    uint8_t	auth[8];
    uint8_t	virtip[4];
} hsrp_t;

/* ************************************************************
 * DHCP
 * ************************************************************/
#define DHCP_CLIENT_PORT	68
#define DHCP_SERVER_PORT	67
#define DHCPDISCOVER		1
#define DHCPOFFER		2
#define DHCPREQUEST		3
#define DHCPDECLINE		4
#define DHCPACK			5
#define DHCPNAK			6
#define DHCPRELEASE		7
#define DHCPINFORM		8
typedef struct __attribute__((packed)) {
    uint8_t	msgtype;
    uint8_t	hwtype;
    uint8_t	hwalen;
    uint8_t	hops;
    uint32_t	transid;
    uint16_t	seconds;
    uint16_t	bcastflags;
    uint32_t	ciaddr;
    uint32_t	yiaddr;
    uint32_t	siaddr;
    uint32_t	giaddr;
    uint8_t	chaddr[16];
    uint8_t	sname[64];
    uint8_t	file[128];
    uint8_t	cookie[4];
} dhcp_t;

#define DHCP_OPTION_DISCOVER	53
#define DHCP_OPTION_PARAMETERS	55
#define DHCP_OPTION_CLIENTID	61
typedef struct {
    uint8_t	type;
    uint8_t	length;
    uint8_t	value;
} dhcp_option_t;

#endif /*_PROTOCOLS_H_*/

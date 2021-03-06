/*
 * $Id: hf.h 995 2010-09-21 09:30:30Z aon $
 *
 * Copyright (C) 2001-2003 FhG Fokus
 *
 * This file is part of ser, a free SIP server.
 *
 * ser is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * For a license to use the ser software under conditions
 * other than those described here, or to purchase support for this
 * software, please contact iptel.org by e-mail at the following addresses:
 *    info@iptel.org
 *
 * ser is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 * ---------
 * 2003-02-28 scratchpad compatibility abandoned (jiri)
 * 2003-01-27 next baby-step to removing ZT - PRESERVE_ZT (jiri)
 * 2003-05-01 HDR_ACCEPT added (janakj)
 * 2005-02-14 hdr_flags_t && hdr_flags_f defined, split HDR_xxx into
 *             HDR_xxx_F & HDR_xxx_T [WARNING: don't mix them!] (andrei)
 */


#ifndef HF_H
#define HF_H

#include "../str.h"
#include "../comp_defs.h"



/* header type enum
 * if you add a new type:
 *  - make sure it's not greater than 63
 *  - make sure you add the corresponding flag to the hdr_flags_t defs below
 *  - update clean_hdr_field (in hf.c)
 *  - update sip_msg_cloner (modules/tm/sip_msg.c)
 *  - update parse_headers (msg_parser.c)
 *  - update get_hdr_field (msg_parser.c)
 */

enum _hdr_types_t {
	HDR_ERROR_T					= -1   /* Error while parsing */,
	HDR_OTHER_T					=  0   /* Some other header field */,
	HDR_VIA_T					=  1   /* Via header field */,
	HDR_VIA1_T					=  1   /* First Via header field */,
	HDR_VIA2_T					=  2   /* only used as flag */,
	HDR_TO_T					       /* To header field */,
	HDR_FROM_T					       /* From header field */,
	HDR_CSEQ_T					       /* CSeq header field */,
	HDR_CALLID_T				       /* Call-Id header field */,
	HDR_CONTACT_T				       /* Contact header field */,
	HDR_MAXFORWARDS_T			       /* MaxForwards header field */,
	HDR_ROUTE_T					       /* Route header field */,
	HDR_RECORDROUTE_T			       /* Record-Route header field */,
	HDR_CONTENTTYPE_T			       /* Content-Type header field */,
	HDR_CONTENTLENGTH_T			       /* Content-Length header field */,
	HDR_AUTHORIZATION_T			       /* Authorization header field */,
	HDR_EXPIRES_T				       /* Expires header field */,
	HDR_PROXYAUTH_T				       /* Proxy-Authorization hdr field */,
	HDR_SUPPORTED_T				       /* Supported  header field */,
	HDR_REQUIRE_T				       /* Require header */,
	HDR_PROXYREQUIRE_T			       /* Proxy-Require header field */,
	HDR_UNSUPPORTED_T			       /* Unsupported header field */,
	HDR_ALLOW_T					       /* Allow header field */,
	HDR_EVENT_T					       /* Event header field */,
	HDR_ACCEPT_T				       /* Accept header field */,
	HDR_ACCEPTLANGUAGE_T		       /* Accept-Language header field */,
	HDR_ORGANIZATION_T			       /* Organization header field */,
	HDR_PRIORITY_T				       /* Priority header field */,
	HDR_SUBJECT_T				       /* Subject header field */,
	HDR_USERAGENT_T				       /* User-Agent header field */,
	HDR_ACCEPTDISPOSITION_T		       /* Accept-Disposition hdr field */,
	HDR_CONTENTDISPOSITION_T	       /* Content-Disposition hdr field */,
	HDR_DIVERSION_T				       /* Diversion header field */,
	HDR_RPID_T					       /* Remote-Party-ID header field */,
	HDR_REFER_TO_T				       /* Refer-To header fiels */,
	HDR_SIPIFMATCH_T			       /* SIP-If-Match header field */,
	HDR_SESSIONEXPIRES_T		       /* Session-Expires header */,
	HDR_MIN_SE_T				       /* Min-SE */,
	HDR_SUBSCRIPTION_STATE_T	       /* Subscription-State */,
	HDR_ACCEPTCONTACT_T			       /* Accept-Contact header */,
	HDR_ALLOWEVENTS_T			       /* Allow-Events header */,
	HDR_CONTENTENCODING_T		       /* Content-Encoding header */,
	HDR_REFERREDBY_T			       /* Referred-By header */,
	HDR_REJECTCONTACT_T			       /* Reject-Contact header */,
	HDR_REQUESTDISPOSITION_T	       /* Request-Disposition header */,
	HDR_WWW_AUTHENTICATE_T		       /* WWW-Authenticate header field */,
	HDR_PROXY_AUTHENTICATE_T	       /* Proxy-Authenticate header field */,
	HDR_GEOLOCATION_T			/* Geolocation header field */,
	HDR_ESQK_T				/* ESQK header field, for Emergency Services */,
	HDR_EOH_T					       /* End of message header */
};


typedef unsigned long long hdr_flags_t;

/* type to flag conversion
 * WARNING: HDR_ERROR_T has no corresponding FLAG ! */
#define HDR_T2F(type)	\
		(((type)!=HDR_EOH_T)?((hdr_flags_t)1<<(type)):(~(hdr_flags_t)0))

/* helper macro for easy defining and keeping in sync. the flags enum */
#define HDR_F_DEF(name)		HDR_T2F(HDR_##name##_T)

/* flags definitions
 * (enum won't work with all the compiler (e.g. icc) due to the 64bit size) */
#define HDR_EOH_F					HDR_F_DEF(EOH)
#define HDR_VIA_F					HDR_F_DEF(VIA)
#define HDR_VIA1_F					HDR_F_DEF(VIA1)
#define HDR_VIA2_F					HDR_F_DEF(VIA2)
#define HDR_TO_F					HDR_F_DEF(TO)
#define HDR_FROM_F					HDR_F_DEF(FROM)
#define HDR_CSEQ_F					HDR_F_DEF(CSEQ)
#define HDR_CALLID_F				HDR_F_DEF(CALLID)
#define HDR_CONTACT_F				HDR_F_DEF(CONTACT)
#define HDR_MAXFORWARDS_F			HDR_F_DEF(MAXFORWARDS)
#define HDR_ROUTE_F					HDR_F_DEF(ROUTE)
#define HDR_RECORDROUTE_F			HDR_F_DEF(RECORDROUTE)
#define HDR_CONTENTTYPE_F			HDR_F_DEF(CONTENTTYPE)
#define HDR_CONTENTLENGTH_F			HDR_F_DEF(CONTENTLENGTH)
#define HDR_AUTHORIZATION_F			HDR_F_DEF(AUTHORIZATION)
#define HDR_EXPIRES_F				HDR_F_DEF(EXPIRES)
#define HDR_PROXYAUTH_F				HDR_F_DEF(PROXYAUTH)
#define HDR_SUPPORTED_F				HDR_F_DEF(SUPPORTED)
#define HDR_REQUIRE_F				HDR_F_DEF(REQUIRE)
#define HDR_PROXYREQUIRE_F			HDR_F_DEF(PROXYREQUIRE)
#define HDR_UNSUPPORTED_F			HDR_F_DEF(UNSUPPORTED)
#define HDR_ALLOW_F					HDR_F_DEF(ALLOW)
#define HDR_EVENT_F					HDR_F_DEF(EVENT)
#define HDR_ACCEPT_F				HDR_F_DEF(ACCEPT)
#define HDR_ACCEPTLANGUAGE_F		HDR_F_DEF(ACCEPTLANGUAGE)
#define HDR_ORGANIZATION_F			HDR_F_DEF(ORGANIZATION)
#define HDR_PRIORITY_F				HDR_F_DEF(PRIORITY)
#define HDR_SUBJECT_F				HDR_F_DEF(SUBJECT)
#define HDR_USERAGENT_F				HDR_F_DEF(USERAGENT)
#define HDR_ACCEPTDISPOSITION_F		HDR_F_DEF(ACCEPTDISPOSITION)
#define HDR_CONTENTDISPOSITION_F	HDR_F_DEF(CONTENTDISPOSITION)
#define HDR_DIVERSION_F				HDR_F_DEF(DIVERSION)
#define HDR_RPID_F					HDR_F_DEF(RPID)
#define HDR_REFER_TO_F				HDR_F_DEF(REFER_TO)
#define HDR_SIPIFMATCH_F			HDR_F_DEF(SIPIFMATCH)
#define HDR_SESSIONEXPIRES_F		HDR_F_DEF(SESSIONEXPIRES)
#define HDR_MIN_SE_F				HDR_F_DEF(MIN_SE)
#define HDR_SUBSCRIPTION_STATE_F	HDR_F_DEF(SUBSCRIPTION_STATE)
#define HDR_ACCEPTCONTACT_F			HDR_F_DEF(ACCEPTCONTACT)
#define HDR_ALLOWEVENTS_F			HDR_F_DEF(ALLOWEVENTS)
#define HDR_CONTENTENCODING_F		HDR_F_DEF(CONTENTENCODING)
#define HDR_REFERREDBY_F			HDR_F_DEF(REFERREDBY)
#define HDR_REJECTCONTACT_F			HDR_F_DEF(REJECTCONTACT)
#define HDR_REQUESTDISPOSITION_F	HDR_F_DEF(REQUESTDISPOSITION)
#define HDR_WWW_AUTHENTICATE_F		HDR_F_DEF(WWW_AUTHENTICATE)
#define HDR_PROXY_AUTHENTICATE_F	HDR_F_DEF(PROXY_AUTHENTICATE)
#define HDR_GEOLOCATION_F		HDR_F_DEF(GEOLOCATION)
#define HDR_ESQK_F			HDR_F_DEF(ESQK)

#define HDR_OTHER_F					HDR_F_DEF(OTHER)

typedef enum _hdr_types_t hdr_types_t;

/*
 * Format: name':' body
 */
struct hdr_field {
	hdr_types_t type;       /* Header field type */
	str name;               /* Header field name */
	str body;               /* Header field body (may not include CRLF) */
	int len;		/* length from hdr start until EoHF (incl.CRLF) */
	void* parsed;           /* Parsed data structures */
	struct hdr_field* next; /* Next header field in the list */
};



/* returns true if the header links allocated memory on parse field */
static inline int hdr_allocs_parse(struct hdr_field* hdr)
{
	switch(hdr->type){
		case HDR_VIA_T:
		case HDR_TO_T:
		case HDR_FROM_T:
		case HDR_CONTACT_T:
		case HDR_ROUTE_T:
		case HDR_RECORDROUTE_T:
		case HDR_AUTHORIZATION_T:
		case HDR_EXPIRES_T:
		case HDR_PROXYAUTH_T:
		case HDR_EVENT_T:
		case HDR_ACCEPT_T:
		case HDR_CONTENTDISPOSITION_T:
		case HDR_DIVERSION_T:
		case HDR_RPID_T:
		case HDR_REFER_TO_T:
		case HDR_SUBSCRIPTION_STATE_T:
		case HDR_GEOLOCATION_T:

			return 1;
		default:
			return 0;
	}
}

/* frees a hdr_field structure,
 * WARNING: it frees only parsed (and not name.s, body.s)
 */
void clean_hdr_field(struct hdr_field* hf);


/* frees a hdr_field list,
 * WARNING: frees only ->parsed and ->next
 */
void free_hdr_field_lst(struct hdr_field* hf);

void dump_hdr_field( struct hdr_field* hf );

#endif /* HF_H */

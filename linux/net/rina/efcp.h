/*
 * EFCP (Error and Flow Control Protocol)
 *
 *    Francesco Salvestrini <f.salvestrini@nextworks.it>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef RINA_EFCP_H
#define RINA_EFCP_H

#include "common.h"
#include "du.h"
#include "qos.h"
#include "ipcp.h"
#include "kfa.h"


struct connection {
        port_id_t port_id;

        address_t source_address;
        address_t destination_address;

        cep_id_t  source_cep_id;
        cep_id_t  destination_cep_id;

        qos_id_t  qos_id;

        /* FIXME: Add the list of policies associated with this connection */
};

/* The container holding all the EFCP instances for an IPC Process */
struct efcp_container;

struct efcp_container * efcp_container_create(struct kfa * kfa);
int                     efcp_container_destroy(struct efcp_container * c);
int                     efcp_container_set_dt_cons(struct data_transfer_constants * dt_cons,
                                                   struct efcp_container *          container);
int                     efcp_container_write(struct efcp_container * container,
                                             cep_id_t                cep_id,
                                             struct sdu *            sdu);
int                     efcp_container_receive(struct efcp_container * container,
                                               cep_id_t                cep_id,
                                               struct sdu *            sdu);

/* FIXME: Should a cep_id_t be returned instead ? */
cep_id_t      efcp_connection_create(struct efcp_container * container,
                                     struct connection     * connection);
int           efcp_connection_destroy(struct efcp_container * container,
                                      cep_id_t                id);
int           efcp_connection_update(struct efcp_container * container,
                                     cep_id_t                from,
                                     cep_id_t                to);

struct efcp;

struct efcp * efcp_find(struct efcp_container * container,
                        cep_id_t                id);

/* NOTE: efcp_send() takes the ownership of the passed SDU */
int           efcp_send(struct efcp * instance,
                        struct sdu *  sdu);

#endif

/* RLCMACTest.cpp
 *
 * Copyright (C) 2011 Ivan Klyuchnikov
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */



//#include <BitVector.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "csn1.h"
#include "gsm_rlcmac.h"
#include "gprs_rlcmac.h"
extern "C" {
extern const struct log_info gprs_log_info;
#include "pcu_vty.h"
#include <osmocom/vty/telnet_interface.h>
#include <osmocom/vty/logging.h>
#include <osmocom/core/application.h>
#include <osmocom/core/talloc.h>
}
using namespace std;

void printSizeofRLCMAC()
{
	cout << "sizeof RlcMacUplink_t                       " << sizeof(RlcMacUplink_t) << endl;
	cout << "sizeof Packet_Cell_Change_Failure_t         " << sizeof(Packet_Cell_Change_Failure_t) << endl;
	cout << "sizeof Packet_Control_Acknowledgement_t     " << sizeof(Packet_Control_Acknowledgement_t) << endl;
	cout << "sizeof Packet_Downlink_Ack_Nack_t           " << sizeof(Packet_Downlink_Ack_Nack_t) << endl;
	cout << "sizeof EGPRS_PD_AckNack_t		     " << sizeof(EGPRS_PD_AckNack_t) << endl;
	cout << "sizeof Packet_Uplink_Dummy_Control_Block_t  " << sizeof(Packet_Uplink_Dummy_Control_Block_t) << endl;
	cout << "sizeof Packet_Measurement_Report_t          " << sizeof(Packet_Measurement_Report_t) << endl;
	cout << "sizeof Packet_Resource_Request_t            " << sizeof(Packet_Resource_Request_t) << endl;
	cout << "sizeof Packet_Mobile_TBF_Status_t           " << sizeof(Packet_Mobile_TBF_Status_t) << endl;
	cout << "sizeof Packet_PSI_Status_t                  " << sizeof(Packet_PSI_Status_t) << endl;
	cout << "sizeof Packet_Enh_Measurement_Report_t      " << sizeof(Packet_Enh_Measurement_Report_t) << endl;
	cout << "sizeof Packet_Cell_Change_Notification_t    " << sizeof(Packet_Cell_Change_Notification_t) << endl;
	cout << "sizeof Packet_SI_Status_t                   " << sizeof(Packet_SI_Status_t) << endl;
	cout << "sizeof Additional_MS_Rad_Access_Cap_t       " << sizeof(Additional_MS_Rad_Access_Cap_t) << endl;
	cout << "sizeof Packet_Pause_t                       " << sizeof(Packet_Pause_t) << endl;

	cout << "sizeof RlcMacDownlink_t                       " << sizeof(RlcMacDownlink_t) << endl;
	cout << "sizeof Packet_Access_Reject_t                 " << sizeof(Packet_Access_Reject_t) << endl;
       	cout << "sizeof Packet_Cell_Change_Order_t             " << sizeof(Packet_Cell_Change_Order_t) << endl;
       	cout << "sizeof Packet_Downlink_Assignment_t           " << sizeof(Packet_Downlink_Assignment_t) << endl;
	cout << "sizeof Packet_Measurement_Order_Reduced_t     " << sizeof(Packet_Measurement_Order_Reduced_t) << endl;
	cout << "sizeof Packet_Neighbour_Cell_Data_t           " << sizeof(Packet_Neighbour_Cell_Data_t) << endl;
	cout << "sizeof Packet_Serving_Cell_Data_t             " << sizeof(Packet_Serving_Cell_Data_t) << endl;
	cout << "sizeof Packet_Paging_Request_t                " << sizeof(Packet_Paging_Request_t) << endl;
	cout << "sizeof Packet_PDCH_Release_t                  " << sizeof(Packet_PDCH_Release_t) << endl;
	cout << "sizeof Packet_Polling_Request_t               " << sizeof(Packet_Polling_Request_t) << endl;
	cout << "sizeof Packet_Power_Control_Timing_Advance_t  " << sizeof(Packet_Power_Control_Timing_Advance_t) << endl;
	cout << "sizeof Packet_PRACH_Parameters_t              " << sizeof(Packet_PRACH_Parameters_t) << endl;
	cout << "sizeof Packet_Queueing_Notification_t         " << sizeof(Packet_Queueing_Notification_t) << endl;
	cout << "sizeof Packet_Timeslot_Reconfigure_t          " << sizeof(Packet_Timeslot_Reconfigure_t) << endl;
	cout << "sizeof Packet_TBF_Release_t                   " << sizeof(Packet_TBF_Release_t) << endl;
	cout << "sizeof Packet_Uplink_Ack_Nack_t               " << sizeof(Packet_Uplink_Ack_Nack_t) << endl;
	cout << "sizeof Packet_Uplink_Assignment_t             " << sizeof(Packet_Uplink_Assignment_t) << endl;
	cout << "sizeof Packet_Cell_Change_Continue_t          " << sizeof(Packet_Cell_Change_Continue_t) << endl;
	cout << "sizeof Packet_Handover_Command_t              " << sizeof(Packet_Handover_Command_t) << endl;
	cout << "sizeof Packet_PhysicalInformation_t           " << sizeof(Packet_PhysicalInformation_t) << endl;
	cout << "sizeof Packet_Downlink_Dummy_Control_Block_t  " << sizeof(Packet_Downlink_Dummy_Control_Block_t) << endl;
	cout << "sizeof PSI1_t                " << sizeof(PSI1_t) << endl;
	cout << "sizeof PSI2_t                " << sizeof(PSI2_t) << endl;
	cout << "sizeof PSI3_t                " << sizeof(PSI3_t) << endl;
	cout << "sizeof PSI3_BIS_t            " << sizeof(PSI3_BIS_t) << endl;
	cout << "sizeof PSI4_t                " << sizeof(PSI4_t) << endl;
	cout << "sizeof PSI13_t               " << sizeof(PSI13_t) << endl;
	cout << "sizeof PSI5_t                " << sizeof(PSI5_t) << endl;
}

void testRlcMacDownlink()
{
	struct bitvec *resultVector = bitvec_alloc(23);
	bitvec_unhex(resultVector, "2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b");

	std::string testData[] = {
	"4e082500e3f1a81d080820800b2b2b2b2b2b2b2b2b2b2b", // Packet Downlink Assignment
	"48282407a6a074227201000b2b2b2b2b2b2b2b2b2b2b2b", // Packet Uplink Assignment
	"47240c00400000000000000079eb2ac9402b2b2b2b2b2b", // Packet Uplink Ack Nack
	"47283c367513ba333004242b2b2b2b2b2b2b2b2b2b2b2b"  // Packet Uplink Assignment
	"4913e00850884013a8048b2b2b2b2b2b2b2b2b2b2b2b2b"
	"412430007fffffffffffffffefd19c7ba12b2b2b2b2b2b"
	"41942b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b"
	};

	int testDataSize = sizeof(testData)/sizeof(testData[0]);

	cout << " DOWNLINK " << endl;
	for (int i = 0; i < testDataSize; i++)
	{
		bitvec *vector = bitvec_alloc(23);
		bitvec_unhex(vector, testData[i].c_str());
		cout << "vector1 = ";
		for (int i = 0; i < 23; i++)
		{
			cout << hex << (unsigned)*(vector->data + i);
		}
		cout << endl;
		RlcMacDownlink_t * data = (RlcMacDownlink_t *)malloc(sizeof(RlcMacDownlink_t));
		cout << "=========Start DECODE===========" << endl;
		decode_gsm_rlcmac_downlink(vector, data);
		cout << "+++++++++Finish DECODE++++++++++" << endl;
		cout << "=========Start ENCODE=============" << endl;
		encode_gsm_rlcmac_downlink(resultVector, data);
		cout << "+++++++++Finish ENCODE+++++++++++" << endl;
		cout << "vector1 = ";
		for (int i = 0; i < 23; i++)
		{
			cout << (unsigned)*(vector->data + i);
		}
		cout << endl;
		cout << "vector2 = ";
		for (int i = 0; i < 23; i++)
		{
			cout << (unsigned)*(resultVector->data + i);
		}
		cout << endl;
		if (memcmp(vector->data, resultVector->data, 23) == 0)
		{
			cout << "vector1 == vector2 : TRUE" << endl;
		}
		else
		{
			cout << "vector1 == vector2 : FALSE" << endl;
			exit(-1);
		}
		bitvec_unhex(resultVector, "2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b");
		bitvec_free(vector);
		free(data);
	}

	bitvec_free(resultVector);
}


void testRlcMacUplink()
{
	struct bitvec *resultVector = bitvec_alloc(23);
	bitvec_unhex(resultVector, "2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b");

	std::string testData[] = {
	"400e1e61d11f2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b", // Packet Uplink Dummy Control Block
	"400b8020000000000000002480e00b2b2b2b2b2b2b2b2b", // Packet Downlink Ack/Nack
	"4016713dc094270ca2ae57ef909006aa0fc0001f80222b"  // Packet Resource Request
	"400a9020000000000000003010012a0800132b2b2b2b2b"
	};

	int testDataSize = sizeof(testData)/sizeof(testData[0]);


	cout << " UPLINK " << endl;
	for (int i = 0; i < testDataSize; i++)
	{
		bitvec *vector = bitvec_alloc(23);
		bitvec_unhex(vector, testData[i].c_str());
		cout << "vector1 = ";
		for (int i = 0; i < 23; i++)
		{
			cout << hex << (unsigned)*(vector->data + i);
		}
		cout << endl;
		RlcMacUplink_t * data = (RlcMacUplink_t *)malloc(sizeof(RlcMacUplink_t));
		cout << "=========Start DECODE===========" << endl;
		decode_gsm_rlcmac_uplink(vector, data);
		cout << "+++++++++Finish DECODE++++++++++" << endl;
		cout << "=========Start ENCODE=============" << endl;
		encode_gsm_rlcmac_uplink(resultVector, data);
		cout << "+++++++++Finish ENCODE+++++++++++" << endl;
		cout << "vector1 = ";
		for (int i = 0; i < 23; i++)
		{
			cout << (unsigned)*(vector->data + i);
		}
		cout << endl;
		cout << "vector2 = ";
		for (int i = 0; i < 23; i++)
		{
			cout << (unsigned)*(resultVector->data + i);
		}
		cout << endl;
		if (memcmp(vector->data, resultVector->data, 23) == 0)
		{
			cout << "vector1 == vector2 : TRUE" << endl;
		}
		else
		{
			cout << "vector1 == vector2 : FALSE" << endl;
			exit(-1);
		}
		bitvec_unhex(resultVector, "2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b");
		bitvec_free(vector);
		free(data);
	}

	bitvec_free(resultVector);
}

void *tall_pcu_ctx = talloc_named_const(NULL, 1, "Osmo-PCU context");
struct gprs_rlcmac_bts *gprs_rlcmac_bts;
uint16_t spoof_mcc = 0, spoof_mnc = 0;

struct allocalgo_test {
	int line;
	char algo;
	int concurret_tbf;
	uint8_t ms_class;
	uint8_t ts[8];
	enum gprs_rlcmac_tbf_direction dir;
	int single_slot;
	uint8_t result_first_ts;
	uint8_t result_first_common_ts;
	uint8_t result_ts[8];
} allocalgo_test[] = {
	/*
	            algorithm
	            |    concurrent tbf's allocation as used one line above
	            |    |   class
	            |    |   |   available timeslots
	            |    |   |   |                        direction
	            |    |   |   |                        |                   allocate single slot
	            |    |   |   |                        |                   |  expected first TS
	            |    |   |   |                        |                   |  |  expected control TS
	            |    |   |   |                        |                   |  |  |   expected assignment TS
	 */
	/* single slot, we expect the first slot to be selected */
	{ __LINE__, 'a', 0, 12, {0, 1, 1, 1, 1, 0, 0, 0}, GPRS_RLCMAC_UL_TBF, 1, 1, 1, {0, 1, 0, 0, 0, 0, 0, 0} },
	{ __LINE__, 'a', 1, 12, {0, 1, 1, 1, 1, 0, 0, 0}, GPRS_RLCMAC_DL_TBF, 0, 1, 1, {0, 1, 0, 0, 0, 0, 0, 0} },
	/* ms class 12 with 4 consecutively available timeslots (single slot first, then expand to multiple slots) */
	{ __LINE__, 'b', 0, 12, {0, 1, 1, 1, 1, 0, 0, 0}, GPRS_RLCMAC_DL_TBF, 1, 3, 3, {0, 0, 0, 1, 0, 0, 0, 0} },
	{ __LINE__, 'b', 1, 12, {0, 1, 1, 1, 1, 0, 0, 0}, GPRS_RLCMAC_DL_TBF, 0, 1, 3, {0, 1, 1, 1, 1, 0, 0, 0} },
	/* ms class 12 with 4 consecutively available timeslots (uplink first, then assign downlink) */
	{ __LINE__, 'b', 0, 12, {0, 1, 1, 1, 1, 0, 0, 0}, GPRS_RLCMAC_UL_TBF, 1, 3, 3, {0, 0, 0, 1, 0, 0, 0, 0} },
	{ __LINE__, 'b', 1, 12, {0, 1, 1, 1, 1, 0, 0, 0}, GPRS_RLCMAC_DL_TBF, 0, 1, 3, {0, 1, 1, 1, 1, 0, 0, 0} },
	/* ms class 12 with 5 consecutively available timeslots */
	{ __LINE__, 'b', 0, 12, {0, 1, 1, 1, 1, 1, 0, 0}, GPRS_RLCMAC_DL_TBF, 0, 1, 3, {0, 1, 1, 1, 1, 0, 0, 0} },
	/* ms class 12 with 1 available timeslots (downlink first, then assign uplink) */
	{ __LINE__, 'b', 0, 12, {0, 0, 0, 0, 0, 0, 0, 1}, GPRS_RLCMAC_DL_TBF, 0, 7, 7, {0, 0, 0, 0, 0, 0, 0, 1} },
	{ __LINE__, 'b', 1, 12, {0, 0, 0, 0, 0, 0, 0, 1}, GPRS_RLCMAC_UL_TBF, 0, 7, 7, {0, 0, 0, 0, 0, 0, 0, 1} },
	/* ms class 19 with 6 consecutively available timeslots (uplink first, then assign downlink) */
	{ __LINE__, 'b', 0, 19, {0, 1, 1, 1, 1, 1, 1, 0}, GPRS_RLCMAC_UL_TBF, 0, 4, 4, {0, 0, 0, 0, 1, 0, 0, 0} },
	{ __LINE__, 'b', 1, 19, {0, 1, 1, 1, 1, 1, 1, 0}, GPRS_RLCMAC_DL_TBF, 0, 1, 4, {0, 1, 1, 1, 1, 1, 1, 0} },
	/* ms class 6 with 3 consecutively available timeslots */
	{ __LINE__, 'b', 0,  6, {0, 0, 0, 0, 0, 1, 1, 1}, GPRS_RLCMAC_DL_TBF, 0, 5, 6, {0, 0, 0, 0, 0, 1, 1, 1} },
	/* class 6 with 3 consecutively available timeslots */
	{ __LINE__, 'b', 0,  6, {0, 0, 0, 0, 0, 1, 1, 1}, GPRS_RLCMAC_UL_TBF, 0, 6, 6, {0, 0, 0, 0, 0, 0, 1, 0} },
	{ __LINE__, 'b', 1,  6, {0, 0, 0, 0, 0, 1, 1, 1}, GPRS_RLCMAC_DL_TBF, 0, 5, 6, {0, 0, 0, 0, 0, 1, 1, 1} },
	/* ms class 12 with 1 available timeslot at the end */
	{ __LINE__, 'b', 0, 12, {0, 0, 0, 0, 0, 0, 0, 1}, GPRS_RLCMAC_DL_TBF, 0, 7, 7, {0, 0, 0, 0, 0, 0, 0, 1} },
	{ __LINE__, 'b', 1, 12, {0, 0, 0, 0, 0, 0, 0, 1}, GPRS_RLCMAC_UL_TBF, 0, 7, 7, {0, 0, 0, 0, 0, 0, 0, 1} },
	/* ms class 18 with 8 available timeslots (downlink first, then assign uplink) */
	{ __LINE__, 'b', 0, 18, {1, 1, 1, 1, 1, 1, 1, 1}, GPRS_RLCMAC_DL_TBF, 0, 0, 0, {1, 1, 1, 1, 1, 1, 1, 1} },
	{ __LINE__, 'b', 1, 18, {1, 1, 1, 1, 1, 1, 1, 1}, GPRS_RLCMAC_UL_TBF, 0, 0, 0, {1, 1, 1, 1, 1, 1, 1, 1} },
	/* ms class 19 with 6 consecutively available timeslots (single slot first, then expand to multiple slots) */
	{ __LINE__, 'b', 0, 19, {0, 1, 1, 1, 1, 1, 1, 0}, GPRS_RLCMAC_DL_TBF, 1, 4, 4, {0, 0, 0, 0, 1, 0, 0, 0} },
	{ __LINE__, 'b', 1, 19, {0, 1, 1, 1, 1, 1, 1, 0}, GPRS_RLCMAC_DL_TBF, 0, 1, 4, {0, 1, 1, 1, 1, 1, 1, 0} },
	/* end */
	{ 0, 0, 0,  0, {0, 0, 0, 0, 0, 0, 0, 0}, GPRS_RLCMAC_DL_TBF, 0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0} },
};

void testAllocAlgorithm()
{
	struct gprs_rlcmac_bts *bts;
	struct gprs_rlcmac_tbf *tbf = NULL, *tbf_old = NULL;
	uint8_t tfi, trx, use_trx;
	int i, test = 0;

	bts = gprs_rlcmac_bts =
		talloc_zero(tall_pcu_ctx, struct gprs_rlcmac_bts);

next_test:
	if (allocalgo_test[test].algo == 'b')
		bts->alloc_algorithm = alloc_algorithm_b;
	else
		bts->alloc_algorithm = alloc_algorithm_a;
	printf("Test at line %d\n", allocalgo_test[test].line);
	for (i = 0; i < 8; i++)
		bts->trx[0].pdch[i].enable = allocalgo_test[test].ts[i];

	if (tbf) {
		use_trx = tbf->trx;
	} else {
		use_trx = -1;
	}
	tfi = tfi_alloc(allocalgo_test[test].dir, &trx, use_trx);
	if (tfi < 0) {
		printf("No PDCH resource\n");
		exit(-1);
	}
	/* set number of downlink slots according to multislot class */
	tbf = tbf_alloc(tbf_old, allocalgo_test[test].dir, tfi, trx,
		allocalgo_test[test].ms_class,
		allocalgo_test[test].single_slot);
	if (!tbf) {
		printf("No PDCH ressource\n");
		exit(-1);
	}

	if (tbf->first_ts != allocalgo_test[test].result_first_ts) {
		printf("First TS=%d is not as expected (%d)\n",
			tbf->first_ts, allocalgo_test[test].result_first_ts);
		exit(-1);
	}
	if (tbf->first_common_ts
		 != allocalgo_test[test].result_first_common_ts) {
		printf("First TS=%d is not as expected (%d)\n",
			tbf->first_common_ts,
			allocalgo_test[test].result_first_common_ts);
		exit(-1);
	}
	for (i = 0; i < 8; i++) {
		if (tbf->pdch[i] && allocalgo_test[test].result_ts[i])
			continue;
		if (!tbf->pdch[i] && !allocalgo_test[test].result_ts[i])
			continue;
		printf("TS=%d is not assigned as expected (%d)\n", i,
			allocalgo_test[test].result_ts[i]);
		exit(-1);
	}

	test++;
	if (tbf_old) {
		tbf_free(tbf_old);
		tbf_old = NULL;
	}
	if (allocalgo_test[test].line && allocalgo_test[test].concurret_tbf) {
		tbf_old = tbf;
		goto next_test;
	}
	tbf_free(tbf);
	if (allocalgo_test[test].line)
		goto next_test;

	printf("All alloc-algorithm tests successfull\n");
}

int main(int argc, char *argv[])
{
	osmo_init_logging(&gprs_log_info);
	log_set_log_level(osmo_stderr_target, LOGL_DEBUG);

	//printSizeofRLCMAC();
	testRlcMacDownlink();
	testRlcMacUplink();
	testAllocAlgorithm();

}

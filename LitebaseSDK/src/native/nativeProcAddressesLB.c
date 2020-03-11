#include "tcvm.h"
#include "NativeMethods.h"
#include "utils.h"

void fillNativeProcAddressesLB()
{
   htPutPtr(&htNativeProcAddresses, hashCode("lRI_next"), &lRI_next);
   htPutPtr(&htNativeProcAddresses, hashCode("lRI_nextNotSynced"), &lRI_nextNotSynced);
   htPutPtr(&htNativeProcAddresses, hashCode("lRI_setSynced"), &lRI_setSynced);
   htPutPtr(&htNativeProcAddresses, hashCode("lRI_setNotSynced"), &lRI_setNotSynced);
   htPutPtr(&htNativeProcAddresses, hashCode("lRI_close"), &lRI_close);
   htPutPtr(&htNativeProcAddresses, hashCode("lRI_reset"), &lRI_reset);
   htPutPtr(&htNativeProcAddresses, hashCode("lRI_getShort_i"), &lRI_getShort_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRI_getInt_i"), &lRI_getInt_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRI_getLong_i"), &lRI_getLong_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRI_getFloat_i"), &lRI_getFloat_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRI_getDouble_i"), &lRI_getDouble_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRI_getString_i"), &lRI_getString_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRI_getBlob_i"), &lRI_getBlob_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRI_getDate_i"), &lRI_getDate_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRI_getDateTime_i"), &lRI_getDateTime_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRI_isNull_i"), &lRI_isNull_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_privateGetInstance"), &lLC_privateGetInstance);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_privateGetInstance_s"), &lLC_privateGetInstance_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_privateGetInstance_ss"), &lLC_privateGetInstance_ss);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_getSourcePath"), &lLC_getSourcePath);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_execute_s"), &lLC_execute_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_executeUpdate_s"), &lLC_executeUpdate_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_executeQuery_s"), &lLC_executeQuery_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_prepareStatement_s"), &lLC_prepareStatement_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_getCurrentRowId_s"), &lLC_getCurrentRowId_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_getRowCount_s"), &lLC_getRowCount_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_setRowInc_si"), &lLC_setRowInc_si);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_exists_s"), &lLC_exists_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_closeAll"), &lLC_closeAll);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_purge_s"), &lLC_purge_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_getRowCountDeleted_s"), &lLC_getRowCountDeleted_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_getRowIterator_s"), &lLC_getRowIterator_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_privateGetLogger"), &lLC_privateGetLogger);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_privateSetLogger_l"), &lLC_privateSetLogger_l);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_privateGetDefaultLogger"), &lLC_privateGetDefaultLogger);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_privateDeleteLogFiles"), &lLC_privateDeleteLogFiles);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_privateProcessLogs_Ssb"), &lLC_privateProcessLogs_Ssb);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_recoverTable_s"), &lLC_recoverTable_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_convert_s"), &lLC_convert_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_getSlot"), &lLC_getSlot);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_isOpen_s"), &lLC_isOpen_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_dropDatabase_ssi"), &lLC_dropDatabase_ssi);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_isTableProperlyClosed_s"), &lLC_isTableProperlyClosed_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_listAllTables"), &lLC_listAllTables);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_encryptTables_ssi"), &lLC_encryptTables_ssi);
   htPutPtr(&htNativeProcAddresses, hashCode("lLC_decryptTables_ssi"), &lLC_decryptTables_ssi);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_getResultSetMetaData"), &lRS_getResultSetMetaData);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_close"), &lRS_close);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_beforeFirst"), &lRS_beforeFirst);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_afterLast"), &lRS_afterLast);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_first"), &lRS_first);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_last"), &lRS_last);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_next"), &lRS_next);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_prev"), &lRS_prev);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_getShort_i"), &lRS_getShort_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_getShort_s"), &lRS_getShort_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_getInt_i"), &lRS_getInt_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_getInt_s"), &lRS_getInt_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_getLong_i"), &lRS_getLong_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_getLong_s"), &lRS_getLong_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_getFloat_i"), &lRS_getFloat_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_getFloat_s"), &lRS_getFloat_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_getDouble_i"), &lRS_getDouble_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_getDouble_s"), &lRS_getDouble_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_getChars_i"), &lRS_getChars_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_getChars_s"), &lRS_getChars_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_getString_i"), &lRS_getString_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_getString_s"), &lRS_getString_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_getBlob_i"), &lRS_getBlob_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_getBlob_s"), &lRS_getBlob_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_getStrings_i"), &lRS_getStrings_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_getStrings"), &lRS_getStrings);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_getDate_i"), &lRS_getDate_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_getDate_s"), &lRS_getDate_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_getDateTime_i"), &lRS_getDateTime_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_getDateTime_s"), &lRS_getDateTime_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_absolute_i"), &lRS_absolute_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_relative_i"), &lRS_relative_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_getRow"), &lRS_getRow);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_setDecimalPlaces_ii"), &lRS_setDecimalPlaces_ii);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_getRowCount"), &lRS_getRowCount);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_isNull_i"), &lRS_isNull_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_isNull_s"), &lRS_isNull_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lRS_rowToString"), &lRS_rowToString);
   htPutPtr(&htNativeProcAddresses, hashCode("lRSMD_getColumnCount"), &lRSMD_getColumnCount);
   htPutPtr(&htNativeProcAddresses, hashCode("lRSMD_getColumnDisplaySize_i"), &lRSMD_getColumnDisplaySize_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRSMD_getColumnLabel_i"), &lRSMD_getColumnLabel_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRSMD_getColumnType_i"), &lRSMD_getColumnType_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRSMD_getColumnTypeName_i"), &lRSMD_getColumnTypeName_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRSMD_getColumnTableName_i"), &lRSMD_getColumnTableName_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRSMD_getColumnTableName_s"), &lRSMD_getColumnTableName_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lRSMD_hasDefaultValue_i"), &lRSMD_hasDefaultValue_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRSMD_hasDefaultValue_s"), &lRSMD_hasDefaultValue_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lRSMD_isNotNull_i"), &lRSMD_isNotNull_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRSMD_isNotNull_s"), &lRSMD_isNotNull_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lRSMD_getPKColumnIndices_s"), &lRSMD_getPKColumnIndices_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lRSMD_getPKColumnNames_s"), &lRSMD_getPKColumnNames_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lRSMD_getDefaultValue_i"), &lRSMD_getDefaultValue_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lRSMD_getDefaultValue_s"), &lRSMD_getDefaultValue_s);
   htPutPtr(&htNativeProcAddresses, hashCode("lPS_executeQuery"), &lPS_executeQuery);
   htPutPtr(&htNativeProcAddresses, hashCode("lPS_executeUpdate"), &lPS_executeUpdate);
   htPutPtr(&htNativeProcAddresses, hashCode("lPS_setShort_is"), &lPS_setShort_is);
   htPutPtr(&htNativeProcAddresses, hashCode("lPS_setInt_ii"), &lPS_setInt_ii);
   htPutPtr(&htNativeProcAddresses, hashCode("lPS_setLong_il"), &lPS_setLong_il);
   htPutPtr(&htNativeProcAddresses, hashCode("lPS_setFloat_id"), &lPS_setFloat_id);
   htPutPtr(&htNativeProcAddresses, hashCode("lPS_setDouble_id"), &lPS_setDouble_id);
   htPutPtr(&htNativeProcAddresses, hashCode("lPS_setString_is"), &lPS_setString_is);
   htPutPtr(&htNativeProcAddresses, hashCode("lPS_setBlob_iB"), &lPS_setBlob_iB);
   htPutPtr(&htNativeProcAddresses, hashCode("lPS_setDate_id"), &lPS_setDate_id);
   htPutPtr(&htNativeProcAddresses, hashCode("lPS_setDateTime_id"), &lPS_setDateTime_id);
   htPutPtr(&htNativeProcAddresses, hashCode("lPS_setDateTime_it"), &lPS_setDateTime_it);
   htPutPtr(&htNativeProcAddresses, hashCode("lPS_setNull_i"), &lPS_setNull_i);
   htPutPtr(&htNativeProcAddresses, hashCode("lPS_clearParameters"), &lPS_clearParameters);
   htPutPtr(&htNativeProcAddresses, hashCode("lPS_toString"), &lPS_toString);
   htPutPtr(&htNativeProcAddresses, hashCode("lPS_close"), &lPS_close);
   htPutPtr(&htNativeProcAddresses, hashCode("lPS_isValid"), &lPS_isValid);
}
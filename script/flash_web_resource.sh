cur_path=${PWD}
if [[ "$OSTYPE" == "darwin"* ]]; then
    project_path=$(dirname $(dirname $(realpath $0)))
else 
    project_path=$(dirname $(dirname $(realpath $BASH_SOURCE)))
fi
esp_idf_path=${project_path}/sdk/esp-idf

if [ -z "$IDF_PATH" ]; then
  source ${esp_idf_path}/export.sh
fi

# set variables
PARTITION_LABEL=web
PARTITION_TABLE_OFFSET=0x8000   # defined in sdkconfig (CONFIG_PARTITION_TABLE_OFFSET)
PARTITION_CSV_PATH=${project_path}/partitions.csv
BIN_OUT_PATH=${project_path}/main/web/out/${PARTITION_LABEL}.bin
# TODO: as argument
port=/dev/ttyACM0

# get offset of partition label
PARTITION_OFFSET=$(${python} ${esp_idf_path}/components/partition_table/parttool.py \
                    --partition-table-offset ${PARTITION_TABLE_OFFSET} \
                    --partition-table-file ${PARTITION_CSV_PATH} \
                    get_partition_info --partition-name ${PARTITION_LABEL} --info offset)

# flash manufacturing binary
esptool.py -p ${port} write_flash ${PARTITION_OFFSET} ${BIN_OUT_PATH}
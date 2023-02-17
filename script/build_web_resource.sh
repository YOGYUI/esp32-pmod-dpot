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
BIN_OUT_PATH=${project_path}/main/web/out/${PARTITION_LABEL}.bin
BIN_OUT_DIR=$(dirname ${BIN_OUT_PATH})
PARTITION_TABLE_OFFSET=0x8000
SPIFFS_PAGE_SIZE=256
SPIFFS_OBJ_NAME_LEN=32
SPIFFS_META_LENGTH=4
PARTITION_CSV_PATH=${project_path}/partitions.csv

# build vue-webpack
cd ${project_path}/main/web
npm run build
# move resources
[ -d "$BIN_OUT_DIR" ] && rm -rf "$BIN_OUT_DIR"
mkdir ${BIN_OUT_DIR}
mkdir -p ${BIN_OUT_DIR}/src

cp ${project_path}/main/web/index.html ${BIN_OUT_DIR}/
cp -r ${project_path}/main/web/dist ${BIN_OUT_DIR}/
cp -r ${project_path}/main/web/src/assets ${BIN_OUT_DIR}/src/

# get partition size and offset from partition csv file
PARTITION_SIZE=$(${python} ${esp_idf_path}/components/partition_table/parttool.py \
                    --partition-table-offset ${PARTITION_TABLE_OFFSET} \
                    --partition-table-file ${PARTITION_CSV_PATH} \
                    get_partition_info --partition-name ${PARTITION_LABEL} --info size)
PARTITION_OFFSET=$(${python} ${esp_idf_path}/components/partition_table/parttool.py \
                    --partition-table-offset ${PARTITION_TABLE_OFFSET} \
                    --partition-table-file ${PARTITION_CSV_PATH} \
                    get_partition_info --partition-name ${PARTITION_LABEL} --info offset)
echo "partition (${PARTITION_LABEL}): offset=${PARTITION_OFFSET}, size=${PARTITION_SIZE}"

# create bin file (spiffs image)
$(${python} ${esp_idf_path}/components/spiffs/spiffsgen.py \
  ${PARTITION_SIZE} ${BIN_OUT_DIR} ${BIN_OUT_PATH} \
  --page-size ${SPIFFS_PAGE_SIZE} --obj-name-len ${SPIFFS_OBJ_NAME_LEN} \
  --meta-len ${SPIFFS_META_LENGTH} \
  --use-magic \
  --use-magic-len)
echo "spiffs partition binary file generated >> ${BIN_OUT_PATH}"

cd ${cur_path}
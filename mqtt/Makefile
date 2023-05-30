CC = /home/icdyeing/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
CFLAGS = -g -w -lrt -Wl,-z,relro,-z,now,-z,noexecstack -fno-strict-aliasing -fstack-protector-all -fno-omit-frame-pointer -pipe -Wall -fPIC -MD -MP -fno-common -freg-struct-return  -fno-inline -fno-exceptions -Wfloat-equal -Wshadow -Wformat=2 -Wextra -rdynamic -Wl,-z,relro,-z,noexecstack  -fstrength-reduce -fsigned-char -ffunction-sections -fdata-sections -Wpointer-arith -Wcast-qual -Waggregate-return -Winline -Wunreachable-code -Wcast-align -Wundef -Wredundant-decls  -Wstrict-prototypes -Wmissing-prototypes -Wnested-externs -pie -fPIE -s
# -D _SYS_LOG=1 -shared -fPIC
#-D Linux=1
CXXFLAGS = -O2 -g -Wall -fmessage-length=0 -lrt -Wl,-z,relro,-z,now,-z,noexecstack -fno-strict-aliasing -fno-omit-frame-pointer -pipe -Wall -fPIC -MD -MP -fno-common -freg-struct-return  -fno-inline -fno-exceptions -Wfloat-equal -Wshadow -Wformat=2 -Wextra -rdynamic -Wl,-z,relro,-z,noexecstack -fstack-protector-strong -fstrength-reduce -fno-builtin -fsigned-char -ffunction-sections -fdata-sections -Wpointer-arith -Wcast-qual -Waggregate-return -Winline -Wunreachable-code -Wcast-align -Wundef -Wredundant-decls  -Wstrict-prototypes -Wmissing-prototypes -Wnested-externs

OBJS = hmac_sha256.o mqtt_base.o log_util.o string_util.o cJSON.o json_util.o base.o callback_func.o login.o subscribe.o data_trans.o iota_init.o iota_login.o iota_datatrans.o mqttv5_util.o

#generic_tcp_protocol.o gateway_server_demo.o
#bootstrap_demo.o
#$(warning "OS $(OS)")
#$(warning "OSTYPE $(OSTYPE)")

# 20230424
OBJPUB_auto += $(OBJS) stepping_pub_auto.o
OBJPUB_ctl += $(OBJS) stepping_pub_ctl.o
OBJSUB_cmd += $(OBJS) stepping_sub_cmd.o
OBJ_test += $(OBJS) stepping_test.o

#SSH_SWITCH :=1
ifdef SSH_SWITCH
CFLAGS += -DSSH_SWITCH=1
SSH_OBJS = wss_client.o ssh_client.o
OBJS += $(SSH_OBJS)
endif

HEADER_PATH = -I./include
LIB_PATH = -L./lib
SRC_PATH = ./src

LIBS = $(LIB_PATH) -lpaho-mqtt3as -lssl -lcrypto -lz -lboundscheck -lpthread
ifdef SSH_SWITCH
LIBS += -lnopoll -lssh
endif
#$(LIB_PATH) -lHWMQTT
#$(LIB_PATH) -lpaho-mqtt3cs $(LIB_PATH)

ifeq ($(OS), Windows_NT)
	TARGET = stepping_mqtt
else 
#	TARGET = libHWMQTT.so
	TARGET_PUB_auto = stepping_pub_auto
	TARGET_PUB_ctl = stepping_pub_ctl
	TARGET_SUB_cmd = stepping_sub_cmd
	TARGET_test = stepping_test
endif

$(TARGET_PUB_auto):	$(OBJPUB_auto)
	$(CC) $(CFLAGS) -o $(TARGET_PUB_auto) $(OBJPUB_auto) $(LIBS)

$(TARGET_PUB_ctl):	$(OBJPUB_ctl)
	$(CC) $(CFLAGS) -o $(TARGET_PUB_ctl) $(OBJPUB_ctl) $(LIBS)

$(TARGET_SUB_cmd):	$(OBJSUB_cmd)
	$(CC) $(CFLAGS) -o $(TARGET_SUB_cmd) $(OBJSUB_cmd) $(LIBS)

$(TARGET_test):	$(OBJ_test)
	$(CC) $(CFLAGS) -o $(TARGET_test) $(OBJ_test) $(LIBS)

MOVE:
	mkdir -p output
	mv $(OBJS) output
	mv stepping_pub_auto.o stepping_pub_ctl.o stepping_sub_cmd.o stepping_test.o output 
	mv *.d output


##-----------base----------------##
hmac_sha256.o: $(SRC_PATH)/base/hmac_sha256.c
	$(CC) $(CFLAGS) -c $(SRC_PATH)/base/hmac_sha256.c -o hmac_sha256.o $(HEADER_PATH)/base/ $(HEADER_PATH)/agentlite/ $(HEADER_PATH)/util/ $(HEADER_PATH)/third_party/libboundscheck/ $(HEADER_PATH)

mqtt_base.o: $(SRC_PATH)/base/mqtt_base.c
	$(CC) $(CFLAGS) -c $(SRC_PATH)/base/mqtt_base.c -o mqtt_base.o $(HEADER_PATH)/base/ $(HEADER_PATH)/util/ $(HEADER_PATH)/agentlite/

##-----------util----------------##
log_util.o: $(SRC_PATH)/util/log_util.c
	$(CC) $(CFLAGS) -c $(SRC_PATH)/util/log_util.c -o log_util.o $(HEADER_PATH)/util/ $(HEADER_PATH)/agentlite/
	
string_util.o: $(SRC_PATH)/util/string_util.c
	$(CC) $(CFLAGS) -c $(SRC_PATH)/util/string_util.c -o string_util.o $(HEADER_PATH)/util/ $(HEADER_PATH)/agentlite/ $(HEADER_PATH)/third_party/zlib/ $(HEADER_PATH)/third_party/libboundscheck/

mqttv5_util.o: $(SRC_PATH)/util/mqttv5_util.c
	$(CC) $(CFLAGS) -c $(SRC_PATH)/util/mqttv5_util.c -o mqttv5_util.o $(HEADER_PATH)/util/ $(HEADER_PATH)/agentlite/ $(HEADER_PATH)/third_party/zlib/

cJSON.o: $(SRC_PATH)/third_party/cjson/cJSON.c
	$(CC) $(CFLAGS) -c $(SRC_PATH)/third_party/cjson/cJSON.c -o cJSON.o $(HEADER_PATH)/third_party/cjson/ $(HEADER_PATH)/agentlite/
	
json_util.o: $(SRC_PATH)/util/json_util.c
	$(CC) $(CFLAGS) -c $(SRC_PATH)/util/json_util.c -o json_util.o $(HEADER_PATH)/util/ $(HEADER_PATH)/third_party/cjson/ $(HEADER_PATH)/agentlite/

##-----------servcie----------------##
base.o: $(SRC_PATH)/service/base.c
	$(CC) $(CFLAGS) -c $(SRC_PATH)/service/base.c -o base.o $(HEADER_PATH)/service/ $(HEADER_PATH)/base/ $(HEADER_PATH)/agentlite/
	
callback_func.o: $(SRC_PATH)/service/callback_func.c
	$(CC) $(CFLAGS) -c $(SRC_PATH)/service/callback_func.c -o callback_func.o $(HEADER_PATH)/service/ $(HEADER_PATH)/base/ $(HEADER_PATH)/util/ $(HEADER_PATH)/agentlite/ $(HEADER_PATH)/third_party/cjson/ $(HEADER_PATH)
		
login.o: $(SRC_PATH)/service/login.c
	$(CC) $(CFLAGS) -c $(SRC_PATH)/service/login.c -o login.o $(HEADER_PATH)/service/ $(HEADER_PATH)/base/ $(HEADER_PATH)/agentlite/

subscribe.o: $(SRC_PATH)/service/subscribe.c
	$(CC) $(CFLAGS) -c $(SRC_PATH)/service/subscribe.c -o subscribe.o $(HEADER_PATH)/service/ $(HEADER_PATH)/base/ $(HEADER_PATH)/util/ $(HEADER_PATH)/agentlite/
	
data_trans.o: $(SRC_PATH)/service/data_trans.c
	$(CC) $(CFLAGS) -c $(SRC_PATH)/service/data_trans.c -o data_trans.o $(HEADER_PATH)/service/ $(HEADER_PATH)/base/ $(HEADER_PATH)/util/ $(HEADER_PATH)/agentlite/ $(HEADER_PATH)/third_party/cjson/
		

##-----------agentlite----------------##
iota_init.o: $(SRC_PATH)/agentlite/iota_init.c
	$(CC) $(CFLAGS) -c $(SRC_PATH)/agentlite/iota_init.c -o iota_init.o $(HEADER_PATH)/agentlite/ $(HEADER_PATH)/service/ $(HEADER_PATH)/util/

iota_login.o: $(SRC_PATH)/agentlite/iota_login.c
	$(CC) $(CFLAGS) -c $(SRC_PATH)/agentlite/iota_login.c -o iota_login.o $(HEADER_PATH)/agentlite/ $(HEADER_PATH)/service/ $(HEADER_PATH)/agentlite/
	
iota_datatrans.o: $(SRC_PATH)/agentlite/iota_datatrans.c
	$(CC) $(CFLAGS) -c $(SRC_PATH)/agentlite/iota_datatrans.c -o iota_datatrans.o $(HEADER_PATH)/agentlite/ $(HEADER_PATH)/service/ $(HEADER_PATH)/util/ $(HEADER_PATH)/third_party/cjson/  $(HEADER_PATH)/third_party/libboundscheck/ $(HEADER_PATH) 

generic_tcp_protocol.o: $(SRC_PATH)/gateway_demo/generic_tcp_protocol.c
	$(CC) $(CFLAGS) -c $(SRC_PATH)/gateway_demo/generic_tcp_protocol.c -o generic_tcp_protocol.o $(HEADER_PATH)/agentlite/ $(HEADER_PATH)/service/ $(HEADER_PATH)/util/ $(HEADER_PATH)/third_party/cjson/ $(HEADER_PATH)/protocol/ $(HEADER_PATH)
	
gateway_server_demo.o: $(SRC_PATH)/gateway_demo/gateway_server_demo.c
	$(CC) $(CFLAGS) -c $(SRC_PATH)/gateway_demo/gateway_server_demo.c -o gateway_server_demo.o $(HEADER_PATH)/agentlite/ $(HEADER_PATH)/service/ $(HEADER_PATH)/util/ $(HEADER_PATH)/third_party/cjson/ $(HEADER_PATH)/protocol/ $(HEADER_PATH)


# 2023.04.26
stepping_pub_auto.o: $(SRC_PATH)/1stepping/stepping_pub_auto.c
	$(CC) $(CFLAGS) -c $(SRC_PATH)/1stepping/stepping_pub_auto.c -o stepping_pub_auto.o $(HEADER_PATH)/agentlite/ $(HEADER_PATH)/service/ $(HEADER_PATH)/util/ $(HEADER_PATH)/third_party/cjson/ $(HEADER_PATH) $(HEADER_PATH) $(HEADER_PATH)/tunnel/ $(HEADER_PATH)/nopoll
	
stepping_pub_ctl.o: $(SRC_PATH)/1stepping/stepping_pub_ctl.c
	$(CC) $(CFLAGS) -c $(SRC_PATH)/1stepping/stepping_pub_ctl.c -o stepping_pub_ctl.o $(HEADER_PATH)/agentlite/ $(HEADER_PATH)/service/ $(HEADER_PATH)/util/ $(HEADER_PATH)/third_party/cjson/ $(HEADER_PATH) $(HEADER_PATH) $(HEADER_PATH)/tunnel/ $(HEADER_PATH)/nopoll

stepping_sub_cmd.o: $(SRC_PATH)/1stepping/stepping_sub_cmd.c
	$(CC) $(CFLAGS) -c $(SRC_PATH)/1stepping/stepping_sub_cmd.c -o stepping_sub_cmd.o $(HEADER_PATH)/agentlite/ $(HEADER_PATH)/service/ $(HEADER_PATH)/util/ $(HEADER_PATH)/third_party/cjson/ $(HEADER_PATH) $(HEADER_PATH) $(HEADER_PATH)/tunnel/ $(HEADER_PATH)/nopoll

stepping_test.o: $(SRC_PATH)/1stepping/stepping_test.c
	$(CC) $(CFLAGS) -c $(SRC_PATH)/1stepping/stepping_test.c -o stepping_test.o $(HEADER_PATH)/agentlite/ $(HEADER_PATH)/service/ $(HEADER_PATH)/util/ $(HEADER_PATH)/third_party/cjson/ $(HEADER_PATH) $(HEADER_PATH) $(HEADER_PATH)/tunnel/ $(HEADER_PATH)/nopoll




bootstrap_demo.o: $(SRC_PATH)/bootstrap_demo/bootstrap_demo.c
	$(CC) $(CFLAGS) -c $(SRC_PATH)/bootstrap_demo/bootstrap_demo.c -o bootstrap_demo.o $(HEADER_PATH)/agentlite/ $(HEADER_PATH)/service/ $(HEADER_PATH)/util/ $(HEADER_PATH)/third_party/cjson/ $(HEADER_PATH) 
		
##--------------tunnel--------------##
wss_client.o: $(SRC_PATH)/tunnel/wss_client.c
	$(CC) $(CFLAGS) -c $(SRC_PATH)/tunnel/wss_client.c -o wss_client.o $(HEADER_PATH)/nopoll/ $(HEADER_PATH)/agentlite/ $(HEADER_PATH)/util/ $(HEADER_PATH)/tunnel/ $(HEADER_PATH)/third_party/cjson/
ssh_client.o: $(SRC_PATH)/tunnel/ssh_client.c
	$(CC) $(CFLAGS) -c $(SRC_PATH)/tunnel/ssh_client.c -o ssh_client.o $(HEADER_PATH)/nopoll/ $(HEADER_PATH)/agentlite/ $(HEADER_PATH)/util/ $(HEADER_PATH)/tunnel/ $(HEADER_PATH)/ $(HEADER_PATH)/third_party/cjson/ $(HEADER_PATH)/libssh/


all:	$(TARGET_PUB_auto) $(TARGET_PUB_ctl) $(TARGET_SUB_cmd) $(TARGET_test) MOVE

clean:
	rm -f $(TARGET_PUB_auto)
	rm -f $(TARGET_PUB_ctl)
	rm -f $(TARGET_SUB_cmd)
	rm -f $(TARGET_test)
	rm -rf output

.PHONY: obj_static obj_share mk_static mk_share static_all share_all

PRJ_NAME:= hello
STATIC_LIB_NAME:= libhello

CUR_DIR:= .
INC_DIR:= $(CUR_DIR)/inc
SRC_DIR:= $(CUR_DIR)/src
OBJ_DIR:= $(CUR_DIR)/obj
BIN_DIR:= $(CUR_DIR)/bin
LIB_DIR:= $(CUR_DIR)/lib

LIB_STATIC_DIR:= $(LIB_DIR)/static
LIB_SHARE_DIR:= $(LIB_DIR)/share

CC:= gcc
INC_FLAG:= -I $(INC_DIR)

# Create object files for static lib
obj_static:
	$(CC) -c $(CUR_DIR)/main.c -o $(OBJ_DIR)/main.o $(INC_FLAG)
	$(CC) -c $(SRC_DIR)/hello_Tung.c -o $(OBJ_DIR)/hello_Tung.o $(INC_FLAG)
	$(CC) -c $(SRC_DIR)/hello_Word.c -o $(OBJ_DIR)/hello_Word.o $(INC_FLAG)

# Create object file for share lib
obj_share:
	$(CC) -c -fPIC $(CUR_DIR)/main.c -o $(OBJ_DIR)/main.o $(INC_FLAG)
	$(CC) -c -fPIC $(SRC_DIR)/hello_Tung.c -o $(OBJ_DIR)/hello_Tung.o $(INC_FLAG)
	$(CC) -c -fPIC $(SRC_DIR)/hello_Word.c -o $(OBJ_DIR)/hello_Word.o $(INC_FLAG)

mk_static:
	ar rcs $(LIB_STATIC_DIR)/$(STATIC_LIB_NAME).a $(OBJ_DIR)/main.o $(OBJ_DIR)/hello_Tung.o $(OBJ_DIR)/hello_Word.o 

mk_share:
	$(CC) -shared $(OBJ_DIR)/main.o $(OBJ_DIR)/hello_Tung.o $(OBJ_DIR)/hello_Word.o -o $(LIB_SHARE_DIR)/$(STATIC_LIB_NAME).so 

static_all: obj_static mk_static
	$(CC) $(OBJ_DIR)/main.o -L$(LIB_STATIC_DIR) -lhello -o $(BIN_DIR)/exam

share_all: obj_share mk_share
	$(CC) $(OBJ_DIR)/main.o -L$(LIB_SHARE_DIR) -lhello -o $(BIN_DIR)/exam

clean:
	rm -rf $(OBJ_DIR)/*.o $(LIB_STATIC_DIR)/*.a  $(LIB_SHARE_DIR)/*.so $(BIN_DIR)/exam

# Note: before run with share library set path 
# export LD_LIBRARY_PATH=./lib:$LD_LIBRARY_PATH

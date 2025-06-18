CC = mpicc
CFLAGS = -Wall -O2 -IEncrypt -IMPI
LDFLAGS = -lcrypto

SRC = MPI/main.c \
	  MPI/procesamiento.c \
      MPI/client.c \
      MPI/server.c \
      MPI/nodo.c \
      MPI/gpio_control.c \
      Encrypt/encrypt.c

OBJ = $(SRC:.c=.o)
TARGET = programa

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

setup:
	sudo apt update
	sudo apt install -y openmpi-bin libopenmpi-dev libssl-dev

clean:
	rm -f $(OBJ) $(TARGET)

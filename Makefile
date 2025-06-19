CC = mpicc
CFLAGS = -Wall -O2 -IEncrypt -IMPI -IDriver-Biblioteca
LDFLAGS = -L. -lcrypto -LDriver-Biblioteca -luart

# Solo los .c que pertenecen a tu lógica MPI y cifrado
SRC = MPI/main.c \
      MPI/client.c \
      MPI/server.c \
      MPI/nodo.c \
      MPI/procesamiento.c \
      Encrypt/encrypt.c

OBJ = $(SRC:.c=.o)
TARGET = programa

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

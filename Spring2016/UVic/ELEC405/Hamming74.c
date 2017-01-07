/* Hamming Encoding and Decoding functions
  For ELEC 405 Class at UVic

  Developed by: Marc Laventure

  List of TODOs:
    - Pass/return byte (no need for an array, all we need is 8 bits MAX)
    - Unit tests
 */

#include <stdlib.h>
#include <stdio.h>

#define ORIGINAL_MESSAGE_SIZE 4
#define ENCODED_MESSAGE_SIZE 7
#define DECODED_MESSAGE_SIZE 7

int *Hamming74_decode(int pMessage[], uint8_t pCorrection)
{
  // This is our "syndrome" generation
  int *ret = malloc(sizeof(int *) * DECODED_MESSAGE_SIZE);
  for (int i = 0; i < ORIGINAL_MESSAGE_SIZE; i++)
  {
    ret[i] = pMessage[i];
  }
  ret[4] = (pMessage[1] + pMessage[2] + pMessage[3] + pMessage[4]) % 2;
  ret[5] = (pMessage[0] + pMessage[1] + pMessage[3] + pMessage[5]) % 2;
  ret[6] = (pMessage[0] + pMessage[2] + pMessage[3] + pMessage[6]) % 2;

  // We may not want to perform the correction, so its conditional
  if (pCorrection)
  {
    // TODO: Correction I might want here, but will de-couple for now
  }

  return ret;
}

int *Hamming74_encode(int pMessage[])
{
  int *ret = malloc(sizeof(int *) * ENCODED_MESSAGE_SIZE);
  for (int i = 0; i < ORIGINAL_MESSAGE_SIZE; i++)
  {
    ret[i] = pMessage[i];
  }
  ret[4] = (pMessage[1] + pMessage[2] + pMessage[3]) % 2;
  ret[5] = (pMessage[0] + pMessage[1] + pMessage[3]) % 2;
  ret[6] = (pMessage[0] + pMessage[2] + pMessage[3]) % 2;
  return ret;
}

void outputMessages(int pOriginal[], int pEncoded[], int pDecoded[])
{
  for (int i = 0; i < ORIGINAL_MESSAGE_SIZE; i++)
  {
    printf("%d ", pOriginal[i]);
  }
  printf("\n");
  for (int i = 0; i < ENCODED_MESSAGE_SIZE; i++)
  {
    printf("%d ", pEncoded[i]);
  }
  printf("\n");
  for (int i = 0; i < DECODED_MESSAGE_SIZE; i++)
  {
    printf("%d ", pDecoded[i]);
  }
  printf("\ndone\n");
}

int main(void)
{
  // This is for testing purposes at the moment.
  int message[] = {0, 0, 1, 0};
  int *sentMessage;
  int *decodedMessage;

  sentMessage = Hamming74_encode(message);
  decodedMessage = Hamming74_decode(sentMessage, 0);
  outputMessages(message, sentMessage, decodedMessage);

  free(sentMessage);
  free(decodedMessage);

  return 0;
}
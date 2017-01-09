/* Hamming Encoding and Decoding functions
  For ELEC 405 Class at UVic

  Developed by: Marc Laventure

  List of TODOs:
    - Pass/return byte (no need for an array, all we need is 8 bits MAX)
    - Unit tests
    - Remove hard coded parity check matrix
 */

#include <stdlib.h>
#include <stdio.h>

#define ORIGINAL_MESSAGE_SIZE 4
#define ENCODED_MESSAGE_SIZE 7
#define DECODED_MESSAGE_SIZE 7

const int PARITY_CHECK_MATRIX[] = {7, 5, 6, 3, 4, 2, 1};

void printArray(int pOutput[], int pLength)
{
  for (int i = 0; i < pLength; i++)
  {
    printf("%d ", pOutput[i]);
  }
  printf("\n");
}

int *Hamming74_correction(int pBrokenMessage[])
{
  int *ret = malloc(sizeof(int *) * ORIGINAL_MESSAGE_SIZE);
  for (int i = 0; i < DECODED_MESSAGE_SIZE; i++)
  {
    ret[i] = pBrokenMessage[i];
  }

  int syndromeValue = (pBrokenMessage[6] << 2) | (pBrokenMessage[5] << 1) | (pBrokenMessage[4]);
  printf("syndromeValue is %d\n", syndromeValue);

  int indexToFix = -1;
  for (int i = 0; i < DECODED_MESSAGE_SIZE; i++)
  {
    if (syndromeValue == PARITY_CHECK_MATRIX[i])
    {
      printf("Fixing %d\n", i);
      indexToFix = i;
      break;
    }
  }

  if (indexToFix == -1)
  {
    // TODO create error enum and handle properly
    printf("Error finding the index\n");
  }
  else
  {
    ret[indexToFix] = 1 - ret[indexToFix];
  }

  ret[4] = 0;
  ret[5] = 0;
  ret[6] = 0;

  return ret;
}

int *Hamming74_decode(int pMessage[], uint8_t pCorrection)
{
  // This is our "syndrome" generation
  int *ret = malloc(sizeof(int *) * DECODED_MESSAGE_SIZE);
  for (int i = 0; i < ORIGINAL_MESSAGE_SIZE; i++)
  {
    ret[i] = pMessage[i];
  }
  ret[4] = (pMessage[0] + pMessage[1] + pMessage[2] + pMessage[4]) % 2;
  ret[5] = (pMessage[0] + pMessage[2] + pMessage[3] + pMessage[5]) % 2;
  ret[6] = (pMessage[0] + pMessage[1] + pMessage[3] + pMessage[6]) % 2;

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
  ret[4] = (pMessage[0] + pMessage[1] + pMessage[2]) % 2;
  ret[5] = (pMessage[0] + pMessage[2] + pMessage[3]) % 2;
  ret[6] = (pMessage[0] + pMessage[1] + pMessage[3]) % 2;
  return ret;
}

void outputMessages(int pOriginal[], int pEncoded[], int pDecoded[])
{
  printArray(pOriginal, ORIGINAL_MESSAGE_SIZE);
  printArray(pEncoded, ENCODED_MESSAGE_SIZE);
  printArray(pDecoded, DECODED_MESSAGE_SIZE);
  printf("\ndone\n");
}

int main(void)
{
  // This is for testing purposes at the moment.
  int message[] = {0, 1, 1, 0};
  int *sentMessage;
  int *decodedMessage;
  int errorMessage[] = {0, 1, 0, 0, 0, 1, 1};
  int *correctedMessage;

  sentMessage = Hamming74_encode(message);
  decodedMessage = Hamming74_decode(sentMessage, 0);
  outputMessages(message, sentMessage, decodedMessage);
  printf("Lets break it now!\n");
  sentMessage[2] = 0;
  correctedMessage = Hamming74_correction(sentMessage);
  printf("CORRECTED\n");
  outputMessages(sentMessage, errorMessage, correctedMessage);
  free(correctedMessage);
  free(sentMessage);
  free(decodedMessage);

  return 0;
}
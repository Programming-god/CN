#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

// CRC-CCITT Polynomial: 0x1021 (CRC-16)
#define CRC_POLY 0x1021

// Function to calculate CRC-CCITT
uint16_t calculate_crc(uint8_t data[], int length) {
    uint16_t crc = 0xFFFF;  // Initial CRC value

    for (int i = 0; i < length; i++) {
        crc ^= ((uint16_t)data[i] << 8);  // XOR with current data byte
        for (int j = 0; j < 8; j++) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ CRC_POLY;
            } else {
                crc <<= 1;
            }
        }
    }

    return crc;
}

int main() {
    char data[100];         // Input data
    uint16_t sent_crc;      // CRC sent along with the data
    bool isReceivedValid = true;

    printf("Enter the data to be transmitted: ");
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n")] = '\0';

    int data_length = strlen(data);
    uint16_t calculated_crc = calculate_crc((uint8_t *)data, data_length);

    printf("Input Data: %s\n", data);
    printf("Calculated CRC: 0x%04X\n", calculated_crc);

    // Simulate transmission
    printf("\nSimulating data transmission...\n");
    // In a real scenario, data and calculated CRC would be transmitted together.
    // For this example, we're just pretending the CRC is sent along with the data.
    sent_crc = calculated_crc;

    // Simulate receiving data and CRC
    printf("\nSimulating data reception...\n");
    // In a real scenario, you would receive the data and CRC.
    // Here, we're just setting the received CRC as the sent CRC for the sake of demonstration.
    uint16_t received_crc = sent_crc;

    // Verify received CRC
    if (received_crc != calculated_crc) {
        printf("Received CRC check failed! Data is corrupted.\n");
        isReceivedValid = false;
    } else {
        printf("Received CRC check passed! Data is correct.\n");
    }

    return 0;
}

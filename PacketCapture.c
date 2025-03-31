#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

void packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    printf("Captured a packet of length: %d\n", header->len);
    for (int i = 0; i < header->len; i++) {
        printf("%02x ", packet[i]);
        if ((i + 1) % 16 == 0) printf("\n");
    }
    printf("\n\n");
}

int main() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;

    // Use loopback interface "lo" or virtual Ethernet (e.g., "eth0" or "veth0")
    char *dev = "lo";  // Replace "lo" with your actual interface name if different

    // Open device for packet capture
    handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Could not open device %s: %s\n", dev, errbuf);
        return 2;
    }

    // Capture packets
    printf("Listening on %s...\n", dev);
    pcap_loop(handle, 10, packet_handler, NULL);

    // Close the handle
    pcap_close(handle);
    return 0;
}

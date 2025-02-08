void int_to_str(int num, char *str) {
    int i = 0, rem;
    
    // Handle negative numbers
    if (num < 0) {
        str[i++] = '-';
        num = -num;  // Make number positive for processing
    }

    // Extract digits from least significant to most
    int temp = num;
    while (temp > 0) {
        temp /= 10;
        i++;
    }

    str[i] = '\0'; // Null-terminate the string
    
    // Populate the string with digits in reverse order
    while (num > 0) {
        rem = num % 10;
        str[--i] = rem + '0';  // Convert digit to char
        num /= 10;
    }
}
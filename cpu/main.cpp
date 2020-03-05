#include <iostream>
#include <string>

struct cpuid_res {
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
};

static inline struct cpuid_res cpuid(int op){
    struct cpuid_res result;
    asm volatile(
        "mov %%ebx, %%edi;"
        "cpuid;"
        "mov %%ebx, %%esi;"
        "mov %%edi, %%ebx;"
        : "=a" (result.eax),
          "=S" (result.ebx),
          "=c" (result.ecx),
          "=d" (result.edx)
        : "0" (op)
        : "edi");
    return result;
}

std::string GetCpuManufacturers(){
    struct cpuid_res result = cpuid(0);
    char vendor_name[13];
    vendor_name[0] = (result.ebx >> 0) & 0xff;
    vendor_name[1] = (result.ebx >> 8) & 0xff;
    vendor_name[2] = (result.ebx >> 16) & 0xff;
    vendor_name[3] = (result.ebx >> 24) & 0xff;

    vendor_name[4] = (result.edx >> 0) & 0xff;
    vendor_name[5] = (result.edx >> 8) & 0xff;
    vendor_name[6] = (result.edx >> 16) & 0xff;
    vendor_name[7] = (result.edx >> 24) & 0xff;

    vendor_name[8] = (result.ecx >> 0) & 0xff;
    vendor_name[9] = (result.ecx >> 8) & 0xff;
    vendor_name[10] = (result.ecx >> 16) & 0xff;
    vendor_name[11] = (result.ecx >> 24) & 0xff;

    vendor_name[12] = '\0';
    return std::string(vendor_name,vendor_name+12);
}

int main(){
    std::cout << "type : " << GetCpuManufacturers() << std::endl;
    std::cout << "size : " << GetCpuManufacturers().length() << std::endl;
    return 0;
}

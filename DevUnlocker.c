// немного переделанный QaSpoofer (Silica&Pina), для аткивации DevMode на Testkit с прошивкой от Devkit.
#include <stdio.h>
#include <stdarg.h>

#include <vitasdk.h>
#include <taihen.h>

static int hook1 = -1;
static int hook2 = -1;
static tai_hook_ref_t ref_hook1;
static tai_hook_ref_t ref_hook2;

static int returntrue() {
    return 1;
}
void _start() __attribute__ ((weak, alias ("module_start")));
int module_start(SceSize argc, const void *args)
{
       hook1 = taiHookFunctionExportForKernel(KERNEL_PID,
		&ref_hook1, 
		"SceSysmem",
		0xFD00C69A,
		0x274663A0,
		returntrue);   
	  
       hook2 = taiHookFunctionExportForKernel(KERNEL_PID,
		&ref_hook2, 
		"SceVshBridge",
		0x35C5ACD4,
		0x641890D8,
		returntrue);
		
		
		
	return SCE_KERNEL_START_SUCCESS;
}
int module_stop(SceSize argc, const void *args)
{
	if (hook1 >= 0) taiHookReleaseForKernel(hook1, ref_hook1);
		if (hook2 >= 0) taiHookReleaseForKernel(hook2, ref_hook2);
		
	return SCE_KERNEL_STOP_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tx_onvif_sdk.h"
#include "tx_onvif_define.h"

#define	MULTICAST_IP           "239.255.255.250"
#define	MULTICAST_PORT     3702
#define   USERNAME                  "admin"
#define   PASSWORD                 "admin"


char searchService[128];
char deviceService[128];
char mediaService[128];
char ptzService[128];
char eventService[128];
char imagingService[128];
char deviceioService[128];
char videoSourceToken[128];
char profileToken[128];


void varInit()
{
    memset(deviceService, 0, sizeof(deviceService));
    memset(mediaService, 0, sizeof(mediaService));
    memset(ptzService, 0, sizeof(ptzService));
    memset(searchService, 0, sizeof(searchService));
    memset(profileToken, 0, sizeof(profileToken));
    memset(deviceioService, 0, sizeof(deviceioService));
	memset(eventService, 0, sizeof(eventService));
    /* PASSWORD = ""; */
    printf("var init OK!\n");
    printf("---------------------------------------------------->\n");
}

void onvif_sleep()
{
    sleep(1);
}

void onvif_discovery1()
{
    TX_ONVIF_REARCH_DEVICEINFO struDiscoveryDeviceInfos[16];
    int deviceNum = 0;
    int ret = TX_ONVIF_Discovery(MULTICAST_IP,  MULTICAST_PORT, struDiscoveryDeviceInfos,  &deviceNum) ;
    printf("============>onvif_discovery ret = %d\n", ret);
    printf("deviceNum = %d\n", deviceNum);
    int i;
    for(i = 0; i< deviceNum; i++)
   {
       printf("i = %d\n Address = %s\n XAddrs = %s\n MetadataVersion = %d\n", i, struDiscoveryDeviceInfos[i].Address, struDiscoveryDeviceInfos[i].XAddrs, struDiscoveryDeviceInfos[i].MetadataVersion);
   }
    char *s = " ";
    char *p;
    p = strtok( struDiscoveryDeviceInfos[0].XAddrs, s);
    while(p)
    {
        printf( "p = %s\n ",p); 
        sprintf(deviceService , p);
        break;
    }
    printf("deviceService = %s", deviceService);
    printf("---------------------------------------------------->\n\n\n");
}

/* 设备测试 */
void onvif_getCapabilities()
{
    TX_ONVIF_CAPABILITY_URI capabilityInfo; 
	memset(&capabilityInfo, 0, sizeof(TX_ONVIF_CAPABILITY_URI));
	printf("device_service = %s\n",deviceService);
	int ret=TX_ONVIF_DEVICE_GetCapabilities( USERNAME, PASSWORD, capability_all, deviceService, &capabilityInfo);
    printf("=============>onvif_getCapabilities ret= %d\n", ret);
    printf("capabilityInfo\n analytics = %s\n device = %s\n events = %s\n imaging = %s\n media = %s\n ptz = %s\n",  capabilityInfo.analytics, capabilityInfo.device, capabilityInfo.events, capabilityInfo.imaging, capabilityInfo.media, capabilityInfo.ptz);
    sprintf(mediaService, capabilityInfo.media);
    sprintf(ptzService, capabilityInfo.ptz);
    sprintf(deviceService, capabilityInfo.device);
    sprintf(imagingService, capabilityInfo.imaging);
    sprintf(deviceioService, capabilityInfo.deviceio);
    sprintf(eventService, capabilityInfo.events);
    printf("deviceioService = %s\n", deviceioService);
	printf("eventService = %s\n", eventService);
    printf("---------------------------------------------------->\n\n\n");
}


void onvif_getDeviceInfo()
{
    TX_ONVIF_DEVICE_INFO deviceInfo;
	memset(&deviceInfo, 0, sizeof(TX_ONVIF_DEVICE_INFO));
	int ret = TX_ONVIF_DEVICE_GetDeviceInformation(USERNAME, PASSWORD,deviceService, &deviceInfo);
    printf("=========>onvif_getDeviceInfo ret = %d\n", ret);
    printf("onvif_getDeviceInfo \n manufacturer = %s\n model = %s\n firmwareVersion = %s\n serialNumber = %s\n hardwareId = %s\n", deviceInfo.manufacturer, deviceInfo.model, deviceInfo.firmwareVersion, deviceInfo.serialNumber, deviceInfo.hardwareId);
    printf("---------------------------------------------------->\n\n\n");
}

void onvif_media_getProfiles()
{
    TX_ONVIF_PROFILES_INFO profileInfo;
    memset(&profileInfo, 0, sizeof(TX_ONVIF_PROFILES_INFO));
	int ret = TX_ONVIF_MEDIA_GetProfiles(USERNAME, PASSWORD, mediaService, &profileInfo);
    sprintf(videoSourceToken, profileInfo.videoSourceToken[0]);
    sprintf(profileToken, profileInfo.token[0]);
    printf("=========>videoSourceToken = %s\n", videoSourceToken);
    printf("=========>onvif_TX_ONVIF_GetProfiles ret = %d\n", ret);
    printf("---------------------------------------------------->\n\n\n");
}

/* device */
void onvif_device_get_services()
{
 	int ret=TX_ONVIF_DEVICE_GetServices(USERNAME, PASSWORD, deviceService );
    printf("=============> ret= %d\n", ret);
    printf("---------------------------------------------------->\n\n\n");   
}

void onvif_device_GetServiceCapabilities()
{
 	int ret=TX_ONVIF_DEVICE_GetServiceCapabilities(USERNAME, PASSWORD, deviceService );
    printf("=============> ret= %d\n", ret);
    printf("---------------------------------------------------->\n\n\n");   
}

void onvif_device_SetSystemFactoryDefault()
{
    int ret=TX_ONVIF_DEVICE_SetSystemFactoryDefault(USERNAME, PASSWORD, deviceService , tx_factory_default_type_soft);
    printf("=============> ret= %d\n", ret);
    printf("---------------------------------------------------->\n\n\n");   
}

void onvif_device_SystemReboot()
{
 	int ret=TX_ONVIF_DEVICE_SystemReboot(USERNAME, PASSWORD, deviceService );
    printf("=============> ret= %d\n", ret);
    printf("---------------------------------------------------->\n\n\n");   
}

void onvif_device_GetUsers()
{
    int ret=TX_ONVIF_DEVICE_GetUsers(USERNAME, PASSWORD, deviceService );
    printf("=============> ret= %d\n", ret);
    printf("---------------------------------------------------->\n\n\n");   
}

void onvif_device_CreateUsers()
{
    char *new_username = "taixin";
    char *new_password = "12345";
        
    int ret=TX_ONVIF_DEVICE_CreateUsers(USERNAME, PASSWORD, deviceService, new_username, new_password,  tx_user_level_operator );
    printf("=============> ret= %d\n", ret);
    printf("---------------------------------------------------->\n\n\n");      
}

void onvif_device_DeleteUsers()
{
    char *del_username = "taixin";
    int ret=TX_ONVIF_DEVICE_DeleteUsers(USERNAME, PASSWORD, deviceService, del_username );
    printf("=============> ret= %d\n", ret);
    printf("---------------------------------------------------->\n\n\n"); 
}

void onvif_device_GetHostname()
{
    int ret=TX_ONVIF_DEVICE_GetHostname(USERNAME, PASSWORD, deviceService );
    printf("=============> ret= %d\n", ret);
    printf("---------------------------------------------------->\n\n\n"); 
}

void onvif_device_SetHostname()
{
    char *new_hostname = "taixin";
    int ret=TX_ONVIF_DEVICE_SetHostname(USERNAME, PASSWORD, deviceService, new_hostname);
    printf("=============> ret= %d\n", ret);
    printf("---------------------------------------------------->\n\n\n"); 
}

void onvif_device_SetHostnameFromDHCP()
{
    int ret=TX_ONVIF_DEVICE_SetHostnameFromDHCP(USERNAME, PASSWORD, deviceService, tx_onvif_false);
    printf("=============> ret= %d\n", ret);
    printf("---------------------------------------------------->\n\n\n"); 
}

void onvif_device_GetDNS()
{
    int ret=TX_ONVIF_DEVICE_GetDNS(USERNAME, PASSWORD, deviceService);
    printf("=============> ret= %d\n", ret);
    printf("---------------------------------------------------->\n\n\n"); 
}

void main_device_test()
{
    /* onvif_device_get_services(); */
    /* onvif_device_GetServiceCapabilities(); */
    /* onvif_device_SetSystemFactoryDefault(); */
    /* onvif_device_SystemReboot(); */
    /* onvif_device_GetUsers(); */
    /* onvif_device_CreateUsers(); */
    /* onvif_device_GetUsers(); */
    /* onvif_device_DeleteUsers(); */
    /* onvif_device_GetUsers(); */
    /* onvif_device_GetHostname(); */
    /* onvif_device_SetHostname(); */
    /* onvif_device_SetHostnameFromDHCP(); */
    onvif_device_GetDNS();
}


/* imaging */
void onvif_imaging_GetServiceCapabilities()
{
    int ret=TX_ONVIF_IMAGING_GetServiceCapabilities(USERNAME, PASSWORD, imagingService);
    printf("=============> ret= %d\n", ret);
    printf("---------------------------------------------------->\n\n\n"); 
}

void onvif_imaging_SetImagingSettings()
{
    TX_ONVIF_IMAGING_SETTINGS imagingSettings;
    memset(&imagingSettings, 0, sizeof(TX_ONVIF_IMAGING_SETTINGS));
    imagingSettings.brightness = 50.0f;
    imagingSettings.colorSaturation = 50.0f;
    imagingSettings.contrast = 50.0f;
    int ret=TX_ONVIF_IMAGING_SetImagingSettings(USERNAME, PASSWORD, imagingService, videoSourceToken, &imagingSettings);
    printf("=============> ret= %d\n", ret);
    printf("---------------------------------------------------->\n\n\n"); 
}

void onvif_imaging_GetImagingSettings()
{
    TX_ONVIF_IMAGING_SETTINGS20 imagingSettings;
    memset(&imagingSettings, 0, sizeof(TX_ONVIF_IMAGING_SETTINGS20));
    int ret=TX_ONVIF_IMAGING_GetImagingSettings(USERNAME, PASSWORD, imagingService, videoSourceToken, &imagingSettings);
    printf("=========>imagingSettings Brightness = %f\n", imagingSettings.brightness);
    printf("=========>imagingSettings ColorSaturation = %f\n", imagingSettings.colorSaturation);
    printf("=========>imagingSettings Contrast = %f\n", imagingSettings.contrast);
    printf("=============> ret= %d\n", ret);
    printf("---------------------------------------------------->\n\n\n"); 
}

void onvif_imaging_GetImagingSettings2()
{
    TX_ONVIF_IMAGING_SETTINGS imagingSettings;
    memset(&imagingSettings, 0, sizeof(TX_ONVIF_IMAGING_SETTINGS));
    int ret=TX_ONVIF_IMAGING_GetImagingSettings2(USERNAME, PASSWORD, imagingService, videoSourceToken, &imagingSettings);
    printf("=========>imagingSettings Brightness = %f\n", imagingSettings.brightness);
    printf("=========>imagingSettings ColorSaturation = %f\n", imagingSettings.colorSaturation);
    printf("=========>imagingSettings Contrast = %f\n", imagingSettings.contrast);
    printf("=============> ret= %d\n", ret);
    printf("---------------------------------------------------->\n\n\n"); 
}


void onvif_media_getStreamURI()
{
    TX_ONVIF_STREAM_URI streamURI;
    memset(&streamURI, 0, sizeof(TX_ONVIF_STREAM_URI));
	int ret = TX_ONVIF_MEDIA_GetStreamURI(USERNAME, PASSWORD, deviceService, &streamURI);
    printf("=========>onvif_TX_ONVIF_getStreamURI ret = %d\n", ret);
    printf("---------------------------------------------------->\n\n\n");
}

void main_imaging_test()
{
    onvif_imaging_GetServiceCapabilities();
    /* onvif_imaging_GetImagingSettings(); */
}

/* ptz */
void onvif_ptz_GetServiceCapabilities()
{
    int ret=TX_ONVIF_PTZ_GetServiceCapabilities(USERNAME, PASSWORD, ptzService);
    printf("=============> ret= %d\n", ret);
    printf("---------------------------------------------------->\n\n\n"); 
}

void onvif_ptz_GotoHomePosition()
{
    int ret=TX_ONVIF_PTZ_GotoHomePosition(USERNAME, PASSWORD, ptzService, profileToken);
    printf("=============> ret= %d\n", ret);
    printf("---------------------------------------------------->\n\n\n"); 
}

void onvif_ptz_ContinuousMove()
{
    float x = 0.6;
    float y = 0;
    float z = 0;
    int ret=TX_ONVIF_PTZ_ContinuousMove(USERNAME, PASSWORD, ptzService, profileToken,  tx_onvif_ptz_move, x, y, z);
    printf("=============> ret= %d\n", ret);
    printf("---------------------------------------------------->\n\n\n"); 
}

void onvif_ptz_Stop()
{
    int ret=TX_ONVIF_PTZ_Stop(USERNAME, PASSWORD, ptzService, profileToken, tx_onvif_ptz_move);
    printf("=============> ret= %d\n", ret);
    printf("---------------------------------------------------->\n\n\n"); 
}

void main_ptz_test()
{
    /* onvif_ptz_GetServiceCapabilities();     */
    /* onvif_ptz_GotoHomePosition(); */
    onvif_ptz_Stop();
    onvif_ptz_ContinuousMove();
}



/* deviceio */

void onvif_deviceio_GetServiceCapabilities()
{
     int ret=TX_ONVIF_DEVICEIO_GetServiceCapabilities(USERNAME, PASSWORD, deviceioService);
    printf("=============> ret= %d\n", ret);
    printf("---------------------------------------------------->\n\n\n"); 
}

void main_deviceio_test()
{
    onvif_deviceio_GetServiceCapabilities();
}


/* media */
void onvif_media_GetServiceCapabilities()
{
    int ret=TX_ONVIF_MEDIA_GetServiceCapabilities(USERNAME, PASSWORD, mediaService);
    printf("=============> ret= %d\n", ret);
    printf("---------------------------------------------------->\n\n\n"); 
}

void onvif_media_GetVideoSources()
{
 int ret=TX_ONVIF_MEDIA_GetVideoSources(USERNAME, PASSWORD, mediaService);
    printf("=============> ret= %d\n", ret);
    printf("---------------------------------------------------->\n\n\n"); 
}



void main_media_test()
{
    onvif_media_GetServiceCapabilities();
    onvif_media_GetVideoSources();
}


/* recording test */
void onvif_recoding_GetServiceCapabilities()
{
    int ret=TX_ONVIF_RECORDING_GetServiceCapabilities(USERNAME, PASSWORD, "http://192.168.1.111/onvif/recording");
    printf("=============> ret= %d\n", ret);
    printf("---------------------------------------------------->\n\n\n"); 
}

void onvif_recoding_GetRecordings()
{
    int ret=TX_ONVIF_RECORDING_GetRecordings(USERNAME, PASSWORD, "http://192.168.1.111/onvif/recording");
    printf("=============> ret= %d\n", ret);
    printf("---------------------------------------------------->\n\n\n"); 
}

void onvif_recording_GetRecordingConfiguration()
{
    char *recordToken = "OnvifRecordingToken";
    int ret=TX_ONVIF_RECORDING_GetRecordingConfiguration(USERNAME, PASSWORD, "http://192.168.1.111/onvif/recording", recordToken);
    printf("=============> ret= %d\n", ret);
    printf("---------------------------------------------------->\n\n\n"); 
}

void onfi_recording_GetTrackConfiguration()
{
    char *recordToken = "OnvifRecordingToken";
    char *trackToken = "videotrack_token";
    int ret=TX_ONVIF_RECORDING_GetTrackConfiguration(USERNAME, PASSWORD, "http://192.168.1.111/onvif/recording", recordToken, trackToken);
    printf("=============> ret= %d\n", ret);
    printf("---------------------------------------------------->\n\n\n"); 
}

void main_recording_test()
{
    onvif_recoding_GetServiceCapabilities();
    onvif_recoding_GetRecordings();
    onvif_recording_GetRecordingConfiguration();
    onfi_recording_GetTrackConfiguration();
}

/*event*/
void onvif_event_CreatePullPointSubscription()
{
	// TX_ONVIF_STREAM_URI streamURI;
    //memset(&streamURI, 0, sizeof(TX_ONVIF_STREAM_URI));
	//int ret = TX_ONVIF_MEDIA_GetStreamURI(USERNAME, PASSWORD, deviceService, &streamURI);

    TX_ONVIF_EVENT_SUBSCRIPTION subscription;
    memset(&subscription, 0, sizeof(TX_ONVIF_EVENT_SUBSCRIPTION));
    int ret=TX_ONVIF_EVENT_CreatePullPointSubscription(USERNAME, PASSWORD, eventService, &subscription);
    printf("=============> ret= %d\n", ret);
printf("=============> subscription = %s\n", subscription.Address);
    printf("---------------------------------------------------->\n\n\n"); 
}
int main()
{
    printf("start main---------------->\n");
    varInit();
    onvif_discovery1();
    /* onvif_sleep(); */
    onvif_getCapabilities();
    onvif_media_getProfiles();
//onvif_event_CreatePullPointSubscription();
    onvif_media_getStreamURI();
    onvif_imaging_GetServiceCapabilities();
    onvif_imaging_GetImagingSettings2();
    /* onvif_imaging_SetImagingSettings(); */
    onvif_imaging_GetImagingSettings2();
	onvif_sleep();

	int ret3 = TX_ONVIF_EVENT_GetServiceCapabilities(USERNAME, PASSWORD, eventService);

}

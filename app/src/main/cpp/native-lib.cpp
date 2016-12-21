#include <jni.h>
#include <string>
#include "PersistentDataManager.h"


extern "C" {

JNIEXPORT void JNICALL
Java_com_arc_prith_androidremotecontrol_SettingsActivity_savePersistentData(JNIEnv *env,
                                                                            jobject instance) {

    // TODO

}
JNIEXPORT void JNICALL
Java_com_arc_prith_androidremotecontrol_SettingsActivity_setStartCommandString(JNIEnv *env,
                                                                               jobject instance,
                                                                               jstring cmd_) {
    const char *cmd = env->GetStringUTFChars(cmd_, 0);

    // TODO

    env->ReleaseStringUTFChars(cmd_, cmd);
}

JNIEXPORT void JNICALL
Java_com_arc_prith_androidremotecontrol_SettingsActivity_setStopCommandString(JNIEnv *env,
                                                                              jobject instance,
                                                                              jstring cmd_) {
    const char *cmd = env->GetStringUTFChars(cmd_, 0);

    // TODO

    env->ReleaseStringUTFChars(cmd_, cmd);
}

JNIEXPORT void JNICALL
Java_com_arc_prith_androidremotecontrol_SettingsActivity_setVideoName(JNIEnv *env, jobject instance,
                                                                      jint id, jstring name_) {
    const char *name = env->GetStringUTFChars(name_, 0);

    // TODO

    env->ReleaseStringUTFChars(name_, name);
}

JNIEXPORT void JNICALL
Java_com_arc_prith_androidremotecontrol_SettingsActivity_setHostIpAddress(JNIEnv *env,
                                                                          jobject instance,
                                                                          jstring address_) {
    const char *address = env->GetStringUTFChars(address_, 0);

    // TODO

    env->ReleaseStringUTFChars(address_, address);
}

JNIEXPORT void JNICALL
Java_com_arc_prith_androidremotecontrol_SettingsActivity_setHostPortNumber(JNIEnv *env,
                                                                           jobject instance,
                                                                           jint port) {

    // TODO

}

JNIEXPORT jstring JNICALL
Java_com_arc_prith_androidremotecontrol_SettingsActivity_getHostIpAddress(JNIEnv *env,
                                                                          jobject instance) {

    // TODO


    return env->NewStringUTF("127.0.0.1");
}

JNIEXPORT jint JNICALL
Java_com_arc_prith_androidremotecontrol_SettingsActivity_getHostPortNumber(JNIEnv *env,
                                                                           jobject instance) {

    // TODO
    return 10000;
}

JNIEXPORT jstring JNICALL
Java_com_arc_prith_androidremotecontrol_SettingsActivity_getVideoName(JNIEnv *env, jobject instance,
                                                                      jint id) {

    // TODO


    return env->NewStringUTF(id==0?"video1":(id==1?"video2":"video3"));
}

JNIEXPORT jstring JNICALL
Java_com_arc_prith_androidremotecontrol_SettingsActivity_getStopCommandString(JNIEnv *env,
                                                                              jobject instance) {

    // TODO


    return env->NewStringUTF("stop");
}

JNIEXPORT jstring JNICALL
Java_com_arc_prith_androidremotecontrol_SettingsActivity_getStartCommandString(JNIEnv *env,
                                                                               jobject instance) {

    // TODO


    return env->NewStringUTF("start");
}

JNIEXPORT void JNICALL
Java_com_arc_prith_androidremotecontrol_MainActivity_initializeNativeComponents(JNIEnv *env,
                                                                                jobject instance,
                                                                                jstring dataFilePath_) {
    const char *dataFilePath = env->GetStringUTFChars(dataFilePath_, 0);

    std::string filePath(dataFilePath);
    PersistentDataManager::getInstance().setDataFile(filePath);

    env->ReleaseStringUTFChars(dataFilePath_, dataFilePath);
}

JNIEXPORT jstring JNICALL
Java_com_arc_prith_androidremotecontrol_MainActivity_btnVid1_1OnClick(JNIEnv *env,
                                                                      jobject instance) {

    std::string hello = "Pressed button 1";
    return env->NewStringUTF(hello.c_str());
}


JNIEXPORT jstring JNICALL
Java_com_arc_prith_androidremotecontrol_MainActivity_btnVid2_1OnClick(JNIEnv *env,
                                                                      jobject instance) {
    std::string hello = "Pressed button 2";
    return env->NewStringUTF(hello.c_str());
}

JNIEXPORT jstring JNICALL
Java_com_arc_prith_androidremotecontrol_MainActivity_btnVid3_1OnClick(JNIEnv *env,
                                                                      jobject instance) {

    std::string hello = "Pressed button 3";
    return env->NewStringUTF(hello.c_str());
}
}
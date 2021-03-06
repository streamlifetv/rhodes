/*------------------------------------------------------------------------
* (The MIT License)
* 
* Copyright (c) 2008-2011 Rhomobile, Inc.
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
* 
* http://rhomobile.com
*------------------------------------------------------------------------*/

#include "rhodes/JNIRhodes.h"
#include "rhodes/JNIRhoRuby.h"

#include "rhodes/jni/com_rhomobile_rhodes_signature_Signature.h"

#include "common/app_build_capabilities.h"
#include "common/app_build_configs.h"
#include "common/rhoparams.h"
#include "common/RhodesApp.h"
#include "logging/RhoLog.h"
#include "ruby/ext/rho/rhoruby.h"

#undef DEFAULT_LOGCATEGORY
#define DEFAULT_LOGCATEGORY "Signature"

RHO_GLOBAL void JNICALL Java_com_rhomobile_rhodes_signature_Signature_callback
  (JNIEnv *env, jclass, jstring callback, jstring filePath, jstring error, jboolean cancelled)
{
    rho_rhodesapp_callSignatureCallback(rho_cast<std::string>(callback).c_str(),
        rho_cast<std::string>(filePath).c_str(), rho_cast<std::string>(error).c_str(), cancelled);
}


RHO_GLOBAL void rho_signature_take(char* callback_url, rho_param* p)
{
    JNIEnv *env = jnienv();
    jclass cls = getJNIClass(RHODES_JAVA_CLASS_SIGNATURE);
    if (!cls) return;
    jmethodID mid = getJNIClassStaticMethod(env, cls, "takeSignature", "(Ljava/lang/String;Ljava/lang/Object;)V");
    if (!mid) return;
    jhstring objCallback = rho_cast<jstring>(callback_url);

    jhobject paramsObj = RhoValueConverter(env).createObject(p);
    env->CallStaticVoidMethod(cls, mid, objCallback.get(), paramsObj.get());
}

RHO_GLOBAL void rho_signature_visible(bool visible, rho_param* p)
{
    // check for RhoElements :
    if (!rho_is_rho_elements_extension_can_be_used(get_app_build_config_item("motorola_license"))) {
        RAWLOG_WARNING("Rho::SignatureCapture must be used under RhoElements license! For more information look at http://www.motorolasolutions.com/rhoelements");
    }

    JNIEnv *env = jnienv();
    jclass cls = getJNIClass(RHODES_JAVA_CLASS_SIGNATURE);
    if (!cls) return;
    jmethodID mid = getJNIClassStaticMethod(env, cls, "inline_signature_visible", "(ILjava/lang/Object;)V");
    if (!mid) return;

    jhobject paramsObj = RhoValueConverter(env).createObject(p);
    env->CallStaticVoidMethod(cls, mid, visible, paramsObj.get());
}

RHO_GLOBAL void rho_signature_capture(const char* callback_url) 
{
    // check for RhoElements :
    if (!rho_is_rho_elements_extension_can_be_used(get_app_build_config_item("motorola_license"))) {
        RAWLOG_WARNING("Rho::SignatureCapture must be used under RhoElements license! For more information look at http://www.motorolasolutions.com/rhoelements");
    }
    
    JNIEnv *env = jnienv();
    jclass cls = getJNIClass(RHODES_JAVA_CLASS_SIGNATURE);
    if (!cls) return;
    jmethodID mid = getJNIClassStaticMethod(env, cls, "inline_signature_capture", "(Ljava/lang/String;)V");
    if (!mid) return;
    jhstring objCallback = rho_cast<jstring>(env, callback_url);
    
    env->CallStaticVoidMethod(cls, mid, objCallback.get());
}

RHO_GLOBAL void rho_signature_clear() 
{
    // check for RhoElements :
    if (!rho_is_rho_elements_extension_can_be_used(get_app_build_config_item("motorola_license"))) {
        RAWLOG_WARNING("Rho::SignatureCapture must be used under RhoElements license! For more information look at http://www.motorolasolutions.com/rhoelements");
    }
    
    JNIEnv *env = jnienv();
    jclass cls = getJNIClass(RHODES_JAVA_CLASS_SIGNATURE);
    if (!cls) return;
    jmethodID mid = getJNIClassStaticMethod(env, cls, "inline_signature_clear", "()V");
    if (!mid) return;
    env->CallStaticVoidMethod(cls, mid);
}

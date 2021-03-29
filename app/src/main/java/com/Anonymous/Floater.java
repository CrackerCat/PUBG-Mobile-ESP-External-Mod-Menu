package com.Anonymous;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;

public class Floater extends Service {
    @Override
    public void onCreate() {
        super.onCreate();
		Loader loader = new Loader();
        loader.Init(this,this);
        //xDexLoader.Init(this, this);
    }

    @Override
    public void onDestroy() {
       // xDexLoader.Destroy();
        super.onDestroy();
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }
}

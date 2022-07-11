package net.fogd.lightengine;
 
import android.app.NativeActivity;
import android.os.Bundle;
import android.view.WindowManager;

public class MainActivity extends NativeActivity { 

    static{
        System.loadLibrary("LightEngine");
    }
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
    
    }
	
} 

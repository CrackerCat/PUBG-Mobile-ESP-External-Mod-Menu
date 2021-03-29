package com.Anonymous;
import android.app.*;
import android.content.*;
import android.graphics.*;
import android.net.*;
import android.os.*;
import android.provider.*;
import android.view.*;
import android.view.View.*;
import android.widget.*;
import android.widget.CompoundButton.*;
import java.io.*;
import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.io.IOException;
import android.graphics.Point;
import android.view.WindowManager;

import android.view.Display;

import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;

public class MainActivity extends Activity implements OnClickListener
{
	private int mTouchStartX, mTouchStartY;
    private boolean isMove = false;
	private WindowManager mwindow;
	private WindowManager.LayoutParams lparam;
	private ImageButton mbutton;
	private boolean isDisplay = false;
	
	private boolean isMenuDis = false;
	private View displayMenu;
	private WindowManager mwMenu;
	private WindowManager.LayoutParams mparam;
	private LayoutInflater inflater;
	private View dis;
	
	private View xfc;
	
	private ScrollView itemll;
	private ScrollView vehiclell; 
	private ScrollView playerll; 
	private Button button1;
	private Button button2;
	private Button button3;
	private ImageView imageview1;
	private Button hide;
	private Switch bt1,bt2,bt3,bt4,bt5,bt6,bt7,switch1,switch2,switch3,switch4,switch5;
	
	
	
	SeekBar seekbar1;
	static int shift;
	
	Display d;
	int wi;
	int eii;
	Point size;

	
	
	
	
	

	@Override
	public File getDataDir()
	{
		// TODO: Implement this method
		return super.getDataDir();
	}
	
	
	
	public boolean bu1=false,bu2=false,bu3=false,bu4=false,bu5=false,bu6=false,bu7=false,fkts=false,xssx=false,xswp=false,xscl=false,sw=false;
	static boolean hpp=false,trD=false,enc=false,diss=false;
	
	public void CheckFloatViewPermission()
	{
		if (!Settings.canDrawOverlays(this))
		{
			Toast.makeText(this,"Enable Floating Permission ",Toast.LENGTH_LONG).show();
			startActivityForResult(new Intent(Settings.ACTION_MANAGE_OVERLAY_PERMISSION, Uri.parse("package:" + getPackageName())), 0);
		}
	}
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
		CheckFloatViewPermission();
		Button mbutton1=(Button)findViewById(R.id.b01);
		Button mbutton2=(Button)findViewById(R.id.b02);
		mbutton1.setOnClickListener(this);
		mbutton2.setOnClickListener(this);

		
		//int widthf = getResources().getDisplayMetrics().widthPixels;
		//int hightf = getResources().getDisplayMetrics().heightPixels;
		
		


		Display display = getWindowManager().getDefaultDisplay();
		String displayName = display.getName(); 
		
		Point size = new Point();
		display.getRealSize(size);
		int widthf = size.x;
		int hightf = size.y;
		
		
		
		String output = String.format("%d-%d",hightf,widthf);
		
		
		Writer writer = null;

		try {
			writer = new BufferedWriter(new OutputStreamWriter(
											new FileOutputStream("/sdcard/size.txt"), "utf-8"));
			writer.write(output);
		} catch (IOException ex) {
			// Report
		} finally {
			try {writer.close();} catch (Exception ex) {/*ignore*/}
		}
		
		
		
		
		
		
		//ExecuteElf("su -c");
		
		/*String pathf = getFilesDir().toString()+"/main";
		try
		{	
    OutputStream myOutput = new FileOutputStream(pathf);
	byte[] buffer = new byte[1024];
	int length;
	InputStream myInput = getAssets().open("main");
	while ((length = myInput.read(buffer)) > 0) {
		myOutput.write(buffer, 0, length);
	}
	myInput.close();
	myOutput.flush();
	myOutput.close();
	
		}
		
	
	catch (IOException e)
	{ 
	} */
		
		
		
		//inflater=(LayoutInflater)getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		inflater=inflater.from(this);
		displayMenu=inflater.inflate(R.layout.xf,null);
    }
	public void onClick(View v)
	{
		switch (v.getId())
		{
			case R.id.b01:
			
			    
		
	  startPatcher();
			
			
				//if (isDisplay == false && isMenuDis == false)
					//ShowFloatWindow();
				
				//startService(new Intent(this,FloatingService.class));
				//Toast.makeText(MainActivity.this,"OPEN GAME",Toast.LENGTH_LONG).show();
				
			
			
					
							
				break;
			case R.id.b02:
				if (isDisplay == true)
				{
					
					stopService(new Intent(this, Floater.class));
					//mwindow.removeView(mbutton);//Remove Float
					//isDisplay = false;
					/*if (isMenuDis == true)//If menu Displays 
					{
						mwMenu.removeView(dis);//Remove Menu
						isMenuDis = false;
					}*/
				}
				else
				{
				
				stopService(new Intent(this, Floater.class));
					/*if (isMenuDis == true)
					{
						mwMenu.removeView(dis);//移除菜单
						isMenuDis = false;
					}*/
				}
				Toast.makeText(this,"Closed",Toast.LENGTH_LONG).show();
				break;
			default:
			    Toast.makeText(MainActivity.this,v.getId(),Toast.LENGTH_LONG).show();
		}
	}
	
	private boolean isServiceRunning() {
        ActivityManager manager = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
        if (manager != null) {
            for (ActivityManager.RunningServiceInfo service : manager.getRunningServices(Integer.MAX_VALUE)) {
                if (Floater.class.getName().equals(service.service.getClassName())) {
                    return true;
                }
            }
        }
        return false;
    }
	
	
	void startPatcher() {
        if (Build.VERSION.SDK_INT >= 23 && !Settings.canDrawOverlays(this)) {
            Intent intent = new Intent(Settings.ACTION_MANAGE_OVERLAY_PERMISSION, Uri.parse("package:" + getPackageName()));
            startActivityForResult(intent, 123);
        } else {
            startFloater();
        }
    }

    private void startFloater() {
        if (!isServiceRunning()) {
            startService(new Intent(this, Floater.class));
        } else {
            Toast.makeText(this, "Service Already Running!", Toast.LENGTH_SHORT).show();
        }
    }



	/*private void ShowFloatWindow()
	{
		mwindow=(WindowManager)getApplicationContext().getSystemService(Context.WINDOW_SERVICE);
		lparam=new WindowManager.LayoutParams();
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            lparam.type = WindowManager.LayoutParams.TYPE_APPLICATION_OVERLAY;
        } else {
            lparam.type = WindowManager.LayoutParams.TYPE_PHONE;
        }
		if (Settings.canDrawOverlays(this))
		{
			//mbutton=(ImageButton)findViewById(R.id.xf1);
			mbutton=new ImageButton(getApplicationContext());
			mbutton.setBackgroundResource(R.drawable.icon);
			mbutton.setOnTouchListener(new OnTouchListener() 
			{
			    @Override
				public boolean onTouch(View v, MotionEvent event) 
				{
				    switch (event.getAction()) 
					{
					    case MotionEvent.ACTION_DOWN://单击
						    isMove = false;
						    mTouchStartX = (int) event.getRawX();
						    mTouchStartY = (int) event.getRawY();
						    break;
						case MotionEvent.ACTION_MOVE://拖动
						    int nowX = (int) event.getRawX();
							int nowY = (int) event.getRawY();
							int movedX = nowX - mTouchStartX;
							int movedY = nowY - mTouchStartY;
							if (movedX > 5 || movedY > 5)
							{
							    isMove = true;
				            }
					        mTouchStartX = nowX;
					        mTouchStartY = nowY;
					        lparam.x += movedX;
					        lparam.y += movedY;
					        mwindow.updateViewLayout(mbutton, lparam);
					        break;
					    case MotionEvent.ACTION_UP://抬起
						    break;
						case MotionEvent.ACTION_CANCEL:
						    break;
					}
					    return isMove;
				}
			});
			mbutton.setOnClickListener(new OnClickListener()
			{
				@Override
				public void onClick(View v)
				{
					LoadMenu();
					isMenuDis=true;
					mwindow.removeView(mbutton);
					isDisplay=false;
				}
			});
			//lparam.type=WindowManager.LayoutParams.TYPE_SYSTEM_ERROR;
			//类型
			lparam.format=PixelFormat.RGBA_8888;
			lparam.gravity=Gravity.LEFT;
			lparam.flags=WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
			lparam.width=120;
			//宽度
			lparam.height=120;
			//高度
			if (mparam == null)
			{
				lparam.x=300;//x
				lparam.y=0;//y
			}
			else
			{
				lparam.x=mparam.x;
				lparam.y=mparam.y;//y
			}
			mwindow.addView(mbutton,lparam);
			isDisplay = true;
		}
		else
		{
			Toast.makeText(this,"No Drawing",Toast.LENGTH_LONG).show();
		}
	}
	
	private void LoadMenu()
	{
		mwMenu=(WindowManager)getApplicationContext().getSystemService(Context.WINDOW_SERVICE);
		mparam=new WindowManager.LayoutParams();
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            mparam.type = WindowManager.LayoutParams.TYPE_APPLICATION_OVERLAY;
        } else {
            mparam.type = WindowManager.LayoutParams.TYPE_PHONE;
        }
		
		displayMenu=inflater.inflate(R.layout.xf,null);
		dis=displayMenu.findViewById(R.id.menu);
		//mparam.format=PixelFormat.RGBA_8888;
		mparam.gravity=Gravity.LEFT;
		mparam.flags=WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
		mparam.width=WindowManager.LayoutParams.WRAP_CONTENT;
		//宽度
		mparam.height=WindowManager.LayoutParams.WRAP_CONTENT;
		//高度
		mparam.x=0;//x
		mparam.y=0;//y
		mwMenu.addView(dis,mparam);
		
		
		LinearLayout ll1=displayMenu.findViewById(R.id.menu);
		ll1.setOnTouchListener(new OnTouchListener() 
			{
			    @Override
				public boolean onTouch(View v, MotionEvent event) 
				{
				    switch (event.getAction()) 
					{
					    case MotionEvent.ACTION_DOWN://单击
						    isMove = false;
						    mTouchStartX = (int) event.getRawX();
						    mTouchStartY = (int) event.getRawY();
						    break;
						case MotionEvent.ACTION_MOVE://拖动
						    int nowX = (int) event.getRawX();
							int nowY = (int) event.getRawY();
							int movedX = nowX - mTouchStartX;
							int movedY = nowY - mTouchStartY;
							if (movedX > 5 || movedY > 5)
							{
							    isMove = true;
				            }
					        mTouchStartX = nowX;
					        mTouchStartY = nowY;
					        lparam.x += movedX;
					        lparam.y += movedY;
					        mwindow.updateViewLayout(displayMenu, mparam);
					        break;
					    case MotionEvent.ACTION_UP://抬起
						    break;
						case MotionEvent.ACTION_CANCEL:
						    break;
					}
					return isMove;
				}
			});
		
		ScrollView itemll = displayMenu.findViewById(R.id.itemll);
		itemll.setVisibility(View.GONE);
		
		ScrollView vehiclell = displayMenu.findViewById(R.id.vehiclell);
		vehiclell.setVisibility(View.GONE);
		
		ScrollView playerll = displayMenu.findViewById(R.id.playerll);
		playerll.setVisibility(View.VISIBLE);
		
		
		Button button1 = displayMenu.findViewById(R.id.button1);
		Button button2 = displayMenu.findViewById(R.id.button2);
		Button button3 = displayMenu.findViewById(R.id.button3);
		
		
		SeekBar seekbar1 = displayMenu.findViewById(R.id.seekbar1);



		seekbar1.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {


				public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
					shift = progress;
				}

				public void onStartTrackingTouch(SeekBar seekBar) {
					// TODO Auto-generated method stub
				}

				public void onStopTrackingTouch(SeekBar seekBar) {

				}
			});
		
		
		
		
		
		button1.setOnClickListener(new OnClickListener(){
		@Override
		public void onClick(View v)
				{
				
				ScrollView itemll = displayMenu.findViewById(R.id.itemll);
			ScrollView vehiclell = displayMenu.findViewById(R.id.vehiclell);
			ScrollView playerll = displayMenu.findViewById(R.id.playerll);
					itemll.setVisibility(View.GONE);
					vehiclell.setVisibility(View.GONE);
					playerll.setVisibility(View.VISIBLE);
					
				}
				});
				
		button2.setOnClickListener(new OnClickListener(){
		@Override
		public void onClick(View v)
				{
				
				ScrollView itemll = displayMenu.findViewById(R.id.itemll);
			ScrollView vehiclell = displayMenu.findViewById(R.id.vehiclell);
			ScrollView playerll = displayMenu.findViewById(R.id.playerll);
					itemll.setVisibility(View.GONE);
					vehiclell.setVisibility(View.VISIBLE);
					playerll.setVisibility(View.GONE);
					
				}
				});
				
				
		button3.setOnClickListener(new OnClickListener(){
		@Override
		public void onClick(View v)
				{
				
				ScrollView itemll = displayMenu.findViewById(R.id.itemll);
			ScrollView vehiclell = displayMenu.findViewById(R.id.vehiclell);
			ScrollView playerll = displayMenu.findViewById(R.id.playerll);
					itemll.setVisibility(View.VISIBLE);
					vehiclell.setVisibility(View.GONE);
					playerll.setVisibility(View.GONE);
					
				}
				});
		
		ImageView imageview1 = displayMenu.findViewById(R.id.imageview1);
		
		imageview1.setOnClickListener(new OnClickListener(){
			@Override
				public void onClick(View v)
				{
					//Toast.makeText(MainActivity.this,"on",Toast.LENGTH_LONG).show();
					ShowFloatWindow();

					mwMenu.removeView(dis);
					isMenuDis=false;
				}
		});
		
		
		
		Switch switch1 = displayMenu.findViewById(R.id.switch1);
		Switch switch2 = displayMenu.findViewById(R.id.switch2);
		Switch switch3 = displayMenu.findViewById(R.id.switch3);
		Switch switch4 = displayMenu.findViewById(R.id.switch4);
		Switch switch5 = displayMenu.findViewById(R.id.switch5);
		

			
		switch1=(Switch)displayMenu.findViewById(R.id.switch1);
		switch2=(Switch)displayMenu.findViewById(R.id.switch2);
		switch3=(Switch)displayMenu.findViewById(R.id.switch3);
		switch4=(Switch)displayMenu.findViewById(R.id.switch4);
		switch5=(Switch)displayMenu.findViewById(R.id.switch5);
		
		
		bt1=(Switch)displayMenu.findViewById(R.id.s1);
		bt2=(Switch)displayMenu.findViewById(R.id.wp);
		//bt3=(Switch)displayMenu.findViewById(R.id.c);
		bt4=(Switch)displayMenu.findViewById(R.id.sx);
		bt5=(Switch)displayMenu.findViewById(R.id.fk);
		
		UpdateSwitchButton();         
		
		switch1.setOnCheckedChangeListener(new onc());
		switch2.setOnCheckedChangeListener(new onc());
		switch3.setOnCheckedChangeListener(new onc());
		switch4.setOnCheckedChangeListener(new onc());
		switch5.setOnCheckedChangeListener(new onc());
		
		
		//bt1.setOnCheckedChangeListener(new onc());
		//bt2.setOnCheckedChangeListener(new onc());
		//bt3.setOnCheckedChangeListener(new onc());
		//bt4.setOnCheckedChangeListener(new onc());
		//bt5.setOnCheckedChangeListener(new onc());
	}
	
	private void UpdateSwitchButton()
	{
		
		Switch switch1 = displayMenu.findViewById(R.id.switch1);
		switch1.setChecked(sw);
		
		Switch switch2 = displayMenu.findViewById(R.id.switch2);
		switch2.setChecked(trD);
		
		Switch switch3 = displayMenu.findViewById(R.id.switch3);
		switch3.setChecked(enc);
		
		Switch switch4 = displayMenu.findViewById(R.id.switch4);
		switch4.setChecked(diss);
		
		
		Switch switch5 = displayMenu.findViewById(R.id.switch5);
		switch5.setChecked(hpp);
		
	}
	
	
	
	
	private void ExecuteElf(String shell)
	{
		String s=shell;
		
		try
		{
			Runtime.getRuntime().exec(s,null,null);
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}
	}
	
	private void SaveText(String path,String txt)
	{
		try
		{
			FileOutputStream fos = new FileOutputStream(path);
			fos.write(txt.getBytes());
			fos.close();
		}catch(Exception e){
			e.printStackTrace();
		}
		
	}
	
	class onc implements OnCheckedChangeListener
	{
		@Override
		public void onCheckedChanged(CompoundButton p1, boolean isChecked)
		{
			
                      //  Process process;
			//Toast.makeText(MainActivity.this,"touch",Toast.LENGTH_LONG).show();
			//TODO: Implement this method
				
			switch (p1.getId())
			{
			
					
				case R.id.switch1:
					if (isChecked)
					{
						
                      
					  // String sz = xxxFromJNI();
                       String dt = dataFromJNI();
					   //String vv = nmFromJNI();
                  
           
			
			
						//ExecuteElf("su -c /data/nc/PUBG");
						//TODO
						Datee.setA("Open");
						FloatService.ShowFloat(MainActivity.this);
						Toast.makeText(MainActivity.this,"Start",Toast.LENGTH_LONG).show();
						sw=true;
					}
					else
					{
						//TODO
					
						FloatService.HideFloat();
						Toast.makeText(MainActivity.this,"Close",Toast.LENGTH_LONG).show();
						sw=false;
					}
					break;
					
					
					

				case R.id.switch2:
					if (isChecked)
					{
						trD=true;
					}
					else
					{
						trD=false;
					}
					break;
					
					

				case R.id.switch3:
					if (isChecked)
					{
						enc=true;
					}
					else
					{
						enc=false;
					}
					break;
					
				

				case R.id.switch4:
					if (isChecked)
					{
						diss=true;
					}
					else
					{
						diss=false;
					}
					break;	
					
					
					
				case R.id.switch5:
					if (isChecked)
					{
                       hpp=true;
					}
					else
					{
				       hpp=false;
					}
					break;
					
					
					
					
					
					
				/*case R.id.fk:
					if(isChecked)
					{
					
					File myObj = new File("/sdcard/Android/b.txt"); 
    if (myObj.delete()) { 
		System.out.println("Deleted the file: " + myObj.getName());
    } else {
		System.out.println("Failed to delete the file.");
    }
    
    
						Date.setA("Show Box");
						FloatService.ShowFloat(MainActivity.this);
						Toast.makeText(MainActivity.this,"DONE",Toast.LENGTH_LONG).show();
						fkts=true;
					}
					else
					{
					
					File myObj = new File("/sdcard/Android/b.txt"); 
    if (myObj.delete()) { 
		System.out.println("Deleted the file: " + myObj.getName());
    } else {
		System.out.println("Failed to delete the file.");
    }
					
						//FloatService.HideFloat();
						Toast.makeText(MainActivity.this,"Close",Toast.LENGTH_LONG).show();
						fkts=false;
					}
					break;
					case R.id.sx:
					if (isChecked)
					{
					
					
					
					 try{
                       
                       
                       String path = getFilesDir().toString()+"/main";
                       //String myExec = "/data/user/0/com.tencent.ig.com.pubg.krmobile.com.rekoo.pubgm.com.vng.pubgmobile.ASPCheaT.VM/data/data/root/0/jackpal.androidterm/app_HOME/main";
                       Process  process = Runtime.getRuntime().exec(path);
                         }
                         catch (IOException e) {

                         e.printStackTrace();

                          }
						//TODO
						Date.setA("Display Ray");
						
						//ExecuteElf("su -c /data/nc/hwz");
						FloatService.ShowFloat(MainActivity.this);

						//TODO
						Toast.makeText(MainActivity.this,"Done",Toast.LENGTH_LONG).show();
						xssx=true;
					}
					else
					{
						//TODO

						//TODO
						FloatService.HideFloat();
						Toast.makeText(MainActivity.this,"Close",Toast.LENGTH_LONG).show();
						xssx=false;
					}
					break;
				case R.id.wp:
					if (isChecked)
					{
						//TODO
						Date.setA("Show Items");
						
						
						//ExecuteElf("su -c /data/nc/nwz");
						FloatService.ShowFloat(MainActivity.this);


						//TODO
						Toast.makeText(MainActivity.this,"Done",Toast.LENGTH_LONG).show();
						xswp=true;
					}
					else
					{
						//TODO
						FloatService.HideFloat();

						//TODO
						Toast.makeText(MainActivity.this,"Close",Toast.LENGTH_LONG).show();
						xswp=false;
					}
					break;
			}
			//UpdateSwitchButton();
		}
	}*/
	
	
	/*static {
		try {
			System.loadLibrary("apk");
		}
		catch (Exception e){
			e.getMessage();
		}
	}
	
	static native String  stringFromJNI();
	public native String  dataFromJNI();
	
	public native String  imgFromJNI();
	public native String  nmFromJNI();*/
}

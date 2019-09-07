package com.chenwei116057.plugin;

import android.app.Activity;
import android.os.Bundle;
import android.support.annotation.Nullable;

import com.amap.api.maps.AMap;
import com.amap.api.maps.MapView;
import com.amap.api.maps.model.Marker;
import java.util.ArrayList;

public class AMapPluginActivity extends Activity {
    private MapView mapView;
    private AMap mAMap;
    private static final String TAG = "AMapPluginActivity";
    private boolean needMoveToCenter = Boolean.TRUE;
    private ArrayList<Marker> markers;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
         requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.lay_out);
        //获取地图控件引用
        mapView = (MapView) findViewById(R.id.AMapViewContainer);
        //m.onCreate(savedInstanceState)，创建地图
        mapView.onCreate(savedInstanceState);

    }

    @Override
    protected void onResume() {
        super.onResume();
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
    }
}

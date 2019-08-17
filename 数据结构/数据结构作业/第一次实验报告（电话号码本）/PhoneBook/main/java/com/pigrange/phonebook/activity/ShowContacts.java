package com.pigrange.phonebook.activity;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.MenuItem;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.pigrange.phonebook.R;

public class ShowContacts extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_show_contacts);
        init();
    }

    private void init() {
        TextView tv_name = findViewById(R.id.show_contacts_name);
        TextView tv_number = findViewById(R.id.show_contacts_number);
        TextView tv_address = findViewById(R.id.show_contacts_adress);
        TextView tv_number_extra1 = findViewById(R.id.show_contacts_number_extra1);
        TextView tv_number_extra2 = findViewById(R.id.show_contacts_number_extra2);

        LinearLayout liner_extra1 = findViewById(R.id.show_contacts_linear_1);
        LinearLayout liner_extra2 = findViewById(R.id.show_contacts_linear_2);

        Toolbar toolbar = findViewById(R.id.mtoolBar);
        setSupportActionBar(toolbar);
        ActionBar actionBar = getSupportActionBar();

        if (actionBar != null) {
            actionBar.setDisplayHomeAsUpEnabled(true);
        }

        Intent intent = getIntent();
        String name = intent.getStringExtra(MainActivity.NAME);
        long number = intent.getLongExtra(MainActivity.NUMBER, -1);
        long extra_number1 = intent.getLongExtra(MainActivity.EXTRA_1, -1);
        long extra_number2 = intent.getLongExtra(MainActivity.EXTRA_2, -1);
        String address = intent.getStringExtra(MainActivity.ADDRESS);

        if (number != -1) {
            tv_number.setText(String.valueOf(number));
        }
        if (name != null) {
            tv_name.setText(name);
        }
        if (address != null) {
            tv_address.setText(address);
        }
        if (extra_number1 != -1) {
            tv_number_extra1.setText(String.valueOf(extra_number1));
        } else {
            liner_extra1.setVisibility(View.GONE);
        }
        if (extra_number2 != -1) {
            tv_number_extra2.setText(String.valueOf(extra_number2));
        } else {
            liner_extra2.setVisibility(View.GONE);
        }

    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                finish();
        }
        return super.onOptionsItemSelected(item);
    }
}

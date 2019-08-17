package com.pigrange.phonebook.model;

import org.greenrobot.greendao.annotation.Entity;
import org.greenrobot.greendao.annotation.Id;
import org.greenrobot.greendao.annotation.Generated;

@Entity
public class Contacts extends HasValue {
    @Id(autoincrement = true)
    private Long id;
    private String name;
    private long phoneNumber;
    private long extraNumber1;
    private long extraNumber2;
    private String address;

    @Generated(hash = 56539249)
    public Contacts(Long id, String name, long phoneNumber, long extraNumber1,
            long extraNumber2, String address) {
        this.id = id;
        this.name = name;
        this.phoneNumber = phoneNumber;
        this.extraNumber1 = extraNumber1;
        this.extraNumber2 = extraNumber2;
        this.address = address;
    }

    @Generated(hash = 1804918957)
    public Contacts() {
    }
    
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setPhoneNumber(long phoneNumber) {
        this.phoneNumber = phoneNumber;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    @Override
    public long getValue() {
        return phoneNumber;
    }

    public Long getId() {
        return this.id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public long getPhoneNumber() {
        return this.phoneNumber;
    }

    public long getExtraNumber1() {
        return this.extraNumber1;
    }

    public void setExtraNumber1(long extraNumber1) {
        this.extraNumber1 = extraNumber1;
    }

    public long getExtraNumber2() {
        return this.extraNumber2;
    }

    public void setExtraNumber2(long extraNumber2) {
        this.extraNumber2 = extraNumber2;
    }
}

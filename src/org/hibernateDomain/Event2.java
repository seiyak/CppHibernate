package org.hibernateDomain;

import java.util.Date;
import java.util.List;
import java.util.ArrayList;
import java.util.Set;
import java.util.HashSet;

public class Event2 extends EventParent {
	private Long id;

	private String title;
	private Date date;
	private int value;
	private float floatValue;
	private boolean booleanValue;
	private double doubleValue;
	private long longValue;
	private Event anotherEvent;
	private List list = new ArrayList();
	private Set set = new HashSet();
	private int[] ints;
	private boolean[] booleans;
	private byte[] bytes;
	private char[] chars;
	private short[] shorts;
	private long[] longs;
	private float[] floats;
	private double[] doubles;
	private Boolean[] booleanObjects;

	public Event2() {
		// this form used by Hibernate
	}

	public Event2(String title, Date date) {
		// for application use, to create new events
		this.title = title;
		this.date = date;
	}

	public Long getId() {
		return id;
	}

	public void setId(Long id) {
		this.id = id;
	}

	public Date getDate() {
		return date;
	}

	public void setDate(Date date) {
		this.date = date;
	}

	public String getTitle() {
		return title;
	}

	public void setTitle(String title) {
		this.title = title;
	}

	public int getValue() {
		return this.value;
	}

	public void setValue(int value) {
		this.value = value;
	}

	public Long sampleMethod(int value, boolean b, String str, Double d) {
		return new Long(10);
	}

	public int sampleMethod2(String str, Boolean b, double d, Long l) {
		return 10;
	}

	public void setInts(int[] ints) {
		this.ints = ints;
	}

	public int[] getInts() {
		return this.ints;
	}

	public void setBooleans(boolean[] booleans) {
		this.booleans = booleans;
	}

	public boolean[] getBooleans() {
		return this.booleans;
	}

	public void setBytes(byte[] bytes) {
		this.bytes = bytes;
	}

	public byte[] getBytes() {
		return this.bytes;
	}

	public void setChars(char[] chars) {
		this.chars = chars;
	}

	public char[] getChars() {
		return this.chars;
	}

	public void setShorts(short[] shorts) {
		this.shorts = shorts;
	}

	public short[] getShorts() {
		return this.shorts;
	}

	public void setLongs(long[] longs) {
		this.longs = longs;
	}

	public long[] getLongs() {
		return this.longs;
	}

	public void setFloats(float[] floats) {
		this.floats = floats;
	}

	public float[] getFloats() {
		return this.floats;
	}

	public void setDoubles(double[] doubles) {
		this.doubles = doubles;
	}

	public double[] getDouble() {
		return this.doubles;
	}

	public void setBooleanObjects(Boolean[] booleanObjects) {
		this.booleanObjects = booleanObjects;
	}

	public Boolean[] getBooleanObjects() {
		return this.booleanObjects;
	}
}

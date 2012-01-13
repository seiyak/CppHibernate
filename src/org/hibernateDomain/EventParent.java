package org.hibernateDomain;

public class EventParent{

	private int v;
	protected String strV;
	public Integer intObjV;

	public EventParent(){
	
	}
	
	private String getPrivate(){
		return "private";
	}
	
	protected int getIntV(){
		return 20;
	}
	
	public String getStrV(){
		return "Hello";
	}
	
	public void setIntObjV(Integer intObjV){
		this.intObjV = intObjV;
	}
}
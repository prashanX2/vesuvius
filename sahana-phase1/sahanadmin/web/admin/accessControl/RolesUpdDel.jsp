<%@ page language="java" errorPage="/ErrorDetails.jsp" %>
<jsp:useBean id="RolesBean" scope="request" class="tccsol.admin.accessControl.RolesBean"/>
<jsp:useBean id="ListSBean" scope="session" class="tccsol.util.ListSingleBean" />

<html>
<head>
<title>Access Control - Admin</title>
</head>
<body bgcolor="#FFFFFF">
<%
//Access Control implementation - START
//Modulue Id 8 - System Users
          tccsol.admin.accessControl.LoginBean logb = (tccsol.admin.accessControl.LoginBean) session.getAttribute("LoginBean");
	   boolean isVisible =false;
          byte st = 0;
          if (logb == null)
            st = 1;
          else {
            if (logb.getRoleId() == 0)
                st = 1;
          }
          if (st == 1){
            java.util.Vector v = new java.util.Vector();
            v.add("Please login before you proceed");
            request.setAttribute("messages", v);
            request.getRequestDispatcher("/admin/accessControl/Login1.jsp").forward(request,response);
            return;
          }
	 else{
          	tccsol.admin.accessControl.AccessControl access = new tccsol.admin.accessControl.AccessControl();

          	if (!access.hasAccess(7, logb.getRoleId(), "PAGE", logb.getRoleName(), "Page"))
              {
                 request.setAttribute("messages", access.getMessages());

               }
		else{
		isVisible = true;
		}
	 }

if (request.getAttribute("messages")!=null)
{
    java.util.Vector v = (java.util.Vector) request.getAttribute("messages");
    if (v.size() > 0)
    {
    for(int i=0;i<v.size();i++)
    {
%><li><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
    <%=v.elementAt(i)%></font></li>
<%
    }//end of for loop
    }
}//end of if
if(isVisible){
%>
<a href="/sahanaadmin/admin/accessControl/welcome.jsp">Home</a>
<form action="/sahanaadmin/rolesservlet" method="post" name="frmRolesUpdDel">
  <br>
  <p align="center"><font size="2" face="Verdana, Arial, Helvetica, sans-serif"><strong><u>
  User Roles - Update/Delete</u></strong></font></p>

  <table width="77%" border="0" align="center" cellpadding="0" cellspacing="3">
    <tr>
      <td colspan="3" valign="top">&nbsp;</td>
    </tr>
    <tr>
      <td width="30%" valign="top"><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          Role Name: </font></div></td>
      <td width="40%"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
      <% if (ListSBean.getId() != null) {
            if (ListSBean.getId().trim().length() > 0) {
                RolesBean.setRoleName(ListSBean.getId());
                session.removeAttribute("ListSBean");
            }
         }
      %>
        <input name="roleName" size="30" type="text" id="roleName" value="<%=RolesBean.getRoleName()%>">
        </font></td>
      <td width="30%" valign="top">
     <input name="callAction" type="submit" id="callAction" value="Select From List"></td>
    </tr>
    <tr>
      <td colspan="3" valign="top">&nbsp;</td>
    </tr>
    <tr>
      <td colspan="3" valign="top"><div align="center"><br>
          <input name="callAction" type="submit" id="callAction" value="Update">
          <input name="callAction" type="submit" id="callAction" value="Delete">
          <input type="hidden" name="url" id="url" value="<%=request.getServletPath()%>">
        </div></td>
    </tr>
  </table>
  <p>&nbsp;</p>
</form>
<%}
if (RolesBean != null)
  RolesBean.closeDBConn();

session.removeAttribute("ListSBean");
%>
</body>
</html>

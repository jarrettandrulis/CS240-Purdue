/*
* testuser1 - test
* testuser2 - test
*
*
*
*/

#include <stdio.h>
#include <iostream>
#include <gtk/gtk.h>
#include <time.h>
//#include <curses.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

GtkListStore * list_rooms;
GtkListStore * list_users;
GtkListStore * list_messages;
GtkWidget *lUser;
GtkWidget *lPass;
GtkWidget *lButton;
GtkWidget *rName;
GtkWidget *rButton;
GtkWidget *ltable;
GtkWidget *rtable;
GtkWidget *window;
GtkTreeSelection *selection;
GtkWidget *list;
GtkWidget *list1;
GtkWidget *mlist;
GtkWidget *messages;
GtkWidget *myMessage;
GtkWidget *send_button;
GtkWidget *create_account;
GtkWidget *create_roombtn;
GtkWidget *view1;
GtkWidget *view2;
GtkWidget *entry;
GtkWidget *tv1, *tv2, *tv3;
#define MAX_RESPONSE (10 * 1024)
int z = 0;
char * user = "BAD";
char * password = "BAD";
char * room = "BAD";
char * host;
char * sport;
bool rWin = false;;
bool lWin = false;
GtkWidget *lWindow;
GtkWidget *rWindow;
int port;

static char* copy(const char* orig) {
    char *res = new char[strlen(orig)+1];
    strcpy(res, orig);
    return res;
}
static int open_client_socket(char * host, int port) {
	// Initialize socket address structure
	struct  sockaddr_in socketAddress;
	
	// Clear sockaddr structure
	memset((char *)&socketAddress,0,sizeof(socketAddress));
	
	// Set family to Internet 
	socketAddress.sin_family = AF_INET;
	
	// Set port
	socketAddress.sin_port = htons((u_short)port);
	
	// Get host table entry for this host
	struct  hostent  *ptrh = gethostbyname(host);
	if ( ptrh == NULL ) {
		perror("gethostbyname");
		exit(1);
	}
	
	// Copy the host ip address to socket address structure
	memcpy(&socketAddress.sin_addr, ptrh->h_addr, ptrh->h_length);
	
	// Get TCP transport protocol entry
	struct  protoent *ptrp = getprotobyname("tcp");
	if ( ptrp == NULL ) {
		perror("getprotobyname");
		exit(1);
	}
	
	// Create a tcp socket
	int sock = socket(PF_INET, SOCK_STREAM, ptrp->p_proto);
	if (sock < 0) {
		perror("socket");
		exit(1);
	}
	
	// Connect the socket to the specified server
	if (connect(sock, (struct sockaddr *)&socketAddress,
		    sizeof(socketAddress)) < 0) {
		perror("connect");
		exit(1);
	}
	
	return sock;
}

static int sendCommand(char *  host, int port, const char * command, char * response) {
	
	int sock = open_client_socket( host, port);

	if (sock<0) {
		return 0;
	}

	// Send command
	write(sock, command, strlen(command));
	write(sock, "\r\n",2);

	//Print copy to stdout
	write(1, command, strlen(command));
	write(1, "\r\n",2);

	// Keep reading until connection is closed or MAX_REPONSE
	int n = 0;
	int len = 0;
	while ((n=read(sock, response+len, MAX_RESPONSE - len))>0) {
		len += n;
	}
	response[len]=0;

	printf("response:\n%s\n", response);

	close(sock);

	return 1;
} 
static void hide_login_dialog()
{
	gtk_widget_destroy(lWindow);
}
static void login(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	std::string str = "ADD-USER ";
	str += gtk_entry_get_text(GTK_ENTRY(lUser));
	str += " ";
	str += gtk_entry_get_text(GTK_ENTRY(lPass));
	char response[MAX_RESPONSE];
	sendCommand("localhost",5556,str.c_str(),response);
	if(strlen(response)==4)
	{
		std::string x = gtk_entry_get_text(GTK_ENTRY(lUser));
		user =  new char(x.length());
		strcpy(user,x.c_str());
		x = gtk_entry_get_text(GTK_ENTRY(lPass));
		password = new char(x.length());
		strcpy(password,x.c_str());
		std::string test = "IRC Client: ";
		test += user;
		gtk_window_set_title (GTK_WINDOW (window),test.c_str());
		hide_login_dialog();
	}
	else{
	gtk_window_set_title (GTK_WINDOW (lWindow), "Invalid Password");
	}
}
static gboolean create_login_dialog(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	
    lWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (lWindow), "Login");
    g_signal_connect (lWindow, "destroy",
	              G_CALLBACK (hide_login_dialog), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (lWindow), 10);
    gtk_widget_set_size_request (GTK_WIDGET (lWindow), 300, 200);
    
    ltable = gtk_table_new (6, 4, TRUE);
    gtk_container_add (GTK_CONTAINER (lWindow), ltable);
    gtk_table_set_row_spacings(GTK_TABLE (ltable), 5);
    gtk_table_set_col_spacings(GTK_TABLE (ltable), 5);
    
    lUser = gtk_entry_new_with_buffer(gtk_entry_buffer_new("Username",8));
    gtk_table_attach_defaults(GTK_TABLE(ltable),lUser,0,4,0,2);
    gtk_widget_show(lUser);
    
    lPass = gtk_entry_new_with_buffer(gtk_entry_buffer_new("Password",8));
    gtk_table_attach_defaults(GTK_TABLE(ltable),lPass,0,4,2,4);
    gtk_widget_show(lPass);
    
    lButton = gtk_button_new_with_label ("Login");
    gtk_table_attach_defaults(GTK_TABLE (ltable), lButton, 0, 4, 4, 6); 
    gtk_signal_connect(GTK_OBJECT(lButton),"clicked",GTK_SIGNAL_FUNC(login),(gpointer)"test");
    gtk_widget_show (lButton);
    
    gtk_widget_show (ltable);
	gtk_widget_show(lWindow);
	return true;
}

static void hide_room_dialog()
{
	gtk_widget_destroy(rWindow);
}

static void create_room()
{
	char response[MAX_RESPONSE];
	std::string str = "CREATE-ROOM ";
	str += user;
	str += " ";
	str += password;
	str += " ";
	str += gtk_entry_get_text(GTK_ENTRY(rName));
	sendCommand("localhost",5556,str.c_str(),response);
		std::string str1 = "SEND-MESSAGE ";
		str1 += user;
		str1 += " ";
		str1 += password;
		str1 += " ";
		str1 += room;
		str1 += " ";
		str1 += "has left the room";
		std::string str2 = "LEAVE-ROOM ";
		str2 += user;
		str2 += " ";
		str2 += password;
		str2 += " ";
		str2 += room;
		str2 += " ";
		str2 += "has left the room";
		bool boolean = false;
		std::string x = gtk_entry_get_text(GTK_ENTRY(rName));
	if(strlen(response)==4)
	{
		sendCommand("localhost",5556,str1.c_str(),response);
		boolean = true;
		room =  new char(x.length());
		strcpy(room,x.c_str());
	}
	str = "ENTER-ROOM ";
	str += user;
	str += " ";
	str += password;
	str += " ";
	str += gtk_entry_get_text(GTK_ENTRY(rName));
	sendCommand("localhost",5556,str.c_str(),response);
	if(strlen(response)==4)
	{
		str = "SEND-MESSAGE ";
		str += user;
		str += " ";
		str += password;
		str += " ";
		str += gtk_entry_get_text(GTK_ENTRY(rName));
		str += " ";
		str += "has entered the room";
		sendCommand("localhost",5556,str.c_str(),response);
		if(boolean == false)
		{
				sendCommand("localhost",5556,str1.c_str(),response);
					sendCommand("localhost",5556,str2.c_str(),response);
		}
		
		std::string x = gtk_entry_get_text(GTK_ENTRY(rName));
		room =  new char(x.length());
		strcpy(room,x.c_str());
		hide_room_dialog();
		return;
	}
}

static void create_room_dialog(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{

	rWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (rWindow), "Room Select");
	g_signal_connect (rWindow, "destroy",
	 					G_CALLBACK (hide_room_dialog), NULL);
	gtk_container_set_border_width (GTK_CONTAINER (rWindow), 10);
	gtk_widget_set_size_request (GTK_WIDGET (rWindow), 300, 200);
	rtable = gtk_table_new (6, 4, TRUE);
	gtk_container_add (GTK_CONTAINER (rWindow), rtable);
	gtk_table_set_row_spacings(GTK_TABLE (rtable), 5);
	gtk_table_set_col_spacings(GTK_TABLE (rtable), 5);

	rName = gtk_entry_new_with_buffer(gtk_entry_buffer_new("Room_Name",9));
	gtk_table_attach_defaults(GTK_TABLE(rtable),rName,0,4,0,2);
	gtk_widget_show(rName);

	rButton = gtk_button_new_with_label ("Create Room");
	gtk_table_attach_defaults(GTK_TABLE (rtable), rButton, 0, 4, 4, 6); 
	gtk_signal_connect(GTK_OBJECT(rButton),"clicked",GTK_SIGNAL_FUNC(create_room),(gpointer)"test");
	gtk_widget_show (rButton);

	gtk_widget_show (rtable);
	gtk_widget_show(rWindow);
	return;
}
static gboolean update_list_rooms() {
	
	if(!strcmp(user,"BAD")) return true;
	std::string str = "LIST-ROOMS ";
	str += user;
	str += " ";
	str += password;
	str += " ";
	
	char response[MAX_RESPONSE];
	sendCommand("localhost",5556,str.c_str(),response);
    GtkTreeIter iter;
    int i;
    char * resp;
	gtk_list_store_clear(GTK_LIST_STORE (list_rooms));
	resp = strtok(response,"\r\n");
	while (resp != NULL)
  	{	
    	gchar *msg = g_strdup_printf (resp);
        gtk_list_store_append (GTK_LIST_STORE (list_rooms), &iter);
        gtk_list_store_set (GTK_LIST_STORE (list_rooms), 
	                    &iter,
                        0, msg,
	                    -1);
		g_free (msg);
		resp = strtok(NULL,"\r\n");   
    }
}
static gboolean update_list_users() {
    if(!strcmp(room,"BAD")) return true;
	std::string str = "GET-USERS-IN-ROOM ";
	str += user;
	str += " ";
	str += password;
	str += " ";
	str += room;
	
	char response[MAX_RESPONSE];
	sendCommand("localhost",5556,str.c_str(),response);
    GtkTreeIter iter;
    int i;
    char * resp;
	gtk_list_store_clear(GTK_LIST_STORE (list_users));
	resp = strtok(response,"\r\n");
	while (resp != NULL)
  	{	
    	gchar *msg = g_strdup_printf (resp);
        gtk_list_store_append (GTK_LIST_STORE (list_users), &iter);
        gtk_list_store_set (GTK_LIST_STORE (list_users), 
	                    &iter,
                        0, msg,
	                    -1);
		g_free (msg);
		resp = strtok(NULL,"\r\n");  
    } 
}
static void sendMessage(){
	std::string str = "SEND-MESSAGE ";
	str += user;
	str += " ";
	str += password;
	str += " ";
	str += room;
	str += " ";
	str += gtk_entry_get_text(GTK_ENTRY(entry));
	
	char response[MAX_RESPONSE];
	sendCommand("localhost",5556,str.c_str(),response);
	std::cout << strlen(response) << std::endl;
	if(strlen(response)==4)
	{
		gtk_entry_set_text(GTK_ENTRY(entry),"");
	}
	return;
}


/* Create the list of "messages" */
static GtkWidget *create_list( const char * titleColumn, GtkListStore *model, GtkWidget * tree_vie )
{
    GtkWidget *scrolled_window;
    GtkWidget *tree_view;
    //GtkListStore *model;
    GtkCellRenderer *cell;
    GtkTreeViewColumn *column;

    int i;
   
    /* Create a new scrolled window, with scrollbars only if needed */
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
				    GTK_POLICY_AUTOMATIC, 
				    GTK_POLICY_AUTOMATIC);
   
    //model = gtk_list_store_new (1, G_TYPE_STRING);
    tree_view = gtk_tree_view_new ();
    gtk_container_add (GTK_CONTAINER (scrolled_window), tree_view);
    gtk_tree_view_set_model (GTK_TREE_VIEW (tree_view), GTK_TREE_MODEL (model));
    gtk_widget_show (tree_view);
   
    cell = gtk_cell_renderer_text_new ();

    column = gtk_tree_view_column_new_with_attributes (titleColumn,
                                                       cell,
                                                       "text", 0,
                                                       NULL);
  
    gtk_tree_view_append_column (GTK_TREE_VIEW (tree_view),
	  		         GTK_TREE_VIEW_COLUMN (column));

    return scrolled_window;
}
static gboolean update_messages() {
     if(!strcmp(room,"BAD")) return TRUE;
	std::string str = "GET-MESSAGES ";
	str += user;
	str += " ";
	str += password;
	str += " -1";
	str += " ";
	str += room;
	char response[MAX_RESPONSE];
	sendCommand("localhost",5556,str.c_str(),response);
    GtkTreeIter iter;
    int i;
    char * resp;
	gtk_list_store_clear(GTK_LIST_STORE (list_messages));
	resp = strtok(response,"\r\n");
	while (resp != NULL)
  	{	
  		std::cout << z++ << " " <<resp << std::endl;
    	gchar *msg = g_strdup_printf (resp);
        gtk_list_store_append (GTK_LIST_STORE (list_messages), &iter);
        gtk_list_store_set (GTK_LIST_STORE (list_messages), 
	                    &iter,
                        0, msg,
	                    -1);
		g_free (msg);
		resp = strtok(NULL,"\r\n");  
	}
}
static gboolean update()
{
	update_list_rooms();
	update_list_users();
	update_messages();
	return TRUE;
}

void exitIRC(GtkWidget * w1, gpointer userdata){
  		std::string str1 = "SEND-MESSAGE ";
		str1 += user;
		str1 += " ";
		str1 += password;
		str1 += " ";
		str1 += room;
		str1 += " ";
		str1 += "has left the room";
		char response[MAX_RESPONSE];
		sendCommand("localhost",5556,str1.c_str(),response);
		str1 = "LEAVE-ROOM ";
		str1 += user;
		str1 += " ";
		str1 += password;
		str1 += " ";
		str1 += room;
		str1 += " ";
		str1 += "has left the room";
		sendCommand("localhost",5556,str1.c_str(),response);
		gtk_main_quit();




}

int main( int   argc,
          char *argv[] )
{
	
    gtk_init (&argc, &argv);
   
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "IRC Client");
    g_signal_connect (window, "destroy",
	              G_CALLBACK (exitIRC), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_widget_set_size_request (GTK_WIDGET (window), 450, 400);

    // Create a table to place the widgets. Use a 7x4 Grid (7 rows x 4 columns)
    GtkWidget *table = gtk_table_new (8, 4, TRUE);
    gtk_container_add (GTK_CONTAINER (window), table);
    gtk_table_set_row_spacings(GTK_TABLE (table), 5);
    gtk_table_set_col_spacings(GTK_TABLE (table), 5);
    gtk_widget_show (table);

    // Add list of rooms. Use columns 0 to 4 (exclusive) and rows 0 to 4 (exclusive)
    
    list_rooms = gtk_list_store_new (1, G_TYPE_STRING);
    update_list_rooms();
    tv1 = gtk_tree_view_new ();
    list = create_list ("Rooms", list_rooms,tv1);
    gtk_table_attach_defaults (GTK_TABLE (table), list, 0, 2, 0, 2);
    gtk_widget_show (list);
    
    list_users = gtk_list_store_new (1, G_TYPE_STRING);
    update_list_rooms();
    update_list_users();
    list1 = create_list ("Users in Room", list_users,tv2);
    gtk_table_attach_defaults (GTK_TABLE (table), list1, 2, 4, 0, 2);
    gtk_widget_show (list1);
      list_messages = gtk_list_store_new (1, G_TYPE_STRING);
    mlist = create_list ("Messages", list_messages,tv3);
    gtk_table_attach_defaults (GTK_TABLE (table), mlist, 0, 4, 3, 7);
    gtk_widget_show (mlist);
   
 
	entry = gtk_entry_new ();
	gtk_entry_set_max_length (GTK_ENTRY (entry),0);
	gtk_table_attach_defaults (GTK_TABLE (table), entry, 0, 4, 7, 8);
	gtk_widget_show (entry);

    // Add send button. Use columns 0 to 1 (exclusive) and rows 4 to 7 (exclusive)
    send_button = gtk_button_new_with_label ("Send");
    gtk_table_attach_defaults(GTK_TABLE (table), send_button, 0, 4, 8, 9); 
    gtk_signal_connect(GTK_OBJECT(send_button),"clicked",GTK_SIGNAL_FUNC(sendMessage),(gpointer)"test");
    gtk_widget_show (send_button);
    create_account = gtk_button_new_with_label ("Login/Create Account");
    gtk_table_attach_defaults(GTK_TABLE (table), create_account, 2, 4, 2, 3); 
    gtk_widget_show (create_account);
    gtk_signal_connect(GTK_OBJECT(create_account),"clicked",GTK_SIGNAL_FUNC(create_login_dialog),(gpointer)"test");
    create_roombtn = gtk_button_new_with_label ("Create/Join Room");
    gtk_table_attach_defaults(GTK_TABLE (table), create_roombtn, 0, 2, 2, 3); 
    gtk_signal_connect(GTK_OBJECT(create_roombtn),"clicked",GTK_SIGNAL_FUNC(create_room_dialog),(gpointer)"test");
    gtk_widget_show (create_roombtn);

    
    gtk_widget_show (table);
    gtk_widget_show (window);
    
    //Login Window
	g_timeout_add(1000,(GSourceFunc)update,NULL);
    
    //Room Window



    gtk_main ();

    return 0;
}


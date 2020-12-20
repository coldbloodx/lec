
package main

import "net"
import "os"
import "fmt"


func main(){

    fmt.Println("testline\n");
    
    conn, err := net.Dial("tcp", "192.168.2.138:8080");

    if err != nil {
        fmt.Println("dial error: %s", err);
        defer conn.Close();
        os.Exit(-1);
    }
    
    var buf [512]byte;

    count, err := conn.Read(buf[0:]);

    fmt.Println(string(buf[0:count]));


    os.Exit(0);
}

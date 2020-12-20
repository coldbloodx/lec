
package main

import "net"
import "os"
import "fmt"


func main(){

    fmt.Println("testline\n");

    sock, err := net.Listen("tcp", "192.168.2.138:8080");
    if err != nil {
        fmt.Println(err);
        defer sock.Close();
        os.Exit(-1);
    }

    for {
        conn, err := sock.Accept();

        if err != nil {
            fmt.Println(err);
            defer sock.Close();
            os.Exit(-1);
        }

        fmt.Fprintln(conn, "Hello from TCP server");
    }


    os.Exit(0);
}


package main

import "net"
import "os"
import "fmt"
import "bytes"

import "github.com/davecgh/go-xdr/xdr2"

type data struct {
    stream    [4]byte ;
    clusters  string ;
    ncluster  int    ;
}



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

        var buf [1000]byte;
        nbytes, err := conn.Read(buf[0:1000]);

        fmt.Printf("read %d bytes\n", nbytes);
        fmt.Printf("buf: %+v", buf);

        var mydata data;

        decoder := xdr.NewDecoder(bytes.NewReader(buf[0:1000]));
        
        aaa, _, err := decoder.DecodeFixedOpaque(4);
        /*bbb, _, err := decoder.DecodeString();*/
        /*ccc, _, err := decoder.DecodeUint();  */

        if err != nil {
            fmt.Println(err);
            defer sock.Close();
            os.Exit(-1);
        }
        
        fmt.Printf("aaa: %+v", aaa);
        /*fmt.Printf("bbb: %+v", bbb);*/
        /*fmt.Printf("bbb: %+v", ccc);*/

        fmt.Printf("mydata: %+v", mydata);



    }

    os.Exit(0);
}

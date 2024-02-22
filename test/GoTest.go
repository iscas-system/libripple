package main

// #cgo LDFLAGS: -lripple
// #include <stdlib.h>
// #include <libripple.h>
import "C"
import (
	"fmt"
	"strconv"
	"unsafe"
)

func main() {
	fmt.Println("hello, world")
	nodeCount := 10
	message := (*C.struct_RippleMessage)(C.malloc(C.size_t(C.sizeof_struct_RippleMessage)))
	defer C.free(unsafe.Pointer(message))
	nodeList := (*C.struct_RippleNodeMetadata)(C.malloc(C.size_t(C.sizeof_struct_RippleNodeMetadata * C.int(nodeCount))))
	defer C.free(unsafe.Pointer(nodeList))
	buffer := (*C.struct_RippleNodeMetadata)(C.malloc(C.size_t(C.sizeof_struct_RippleNodeMetadata * C.int(nodeCount))))
	defer C.free(unsafe.Pointer(buffer))

	for i := 0; i < nodeCount; i++ {
		node := (*C.struct_RippleNodeMetadata)(unsafe.Pointer(uintptr(unsafe.Pointer(nodeList)) + uintptr(i*C.sizeof_struct_RippleNodeMetadata)))
		node.Id = C.int(i + 1)
		node.Address = C.CString("192.168.1." + strconv.Itoa(i+1))
		defer C.free(unsafe.Pointer(node.Address))
		node.Port = C.int(8080)
	}

	overlay := C.RippleCreateStarOverlay()
	C.RippleBuildOverlay(overlay, nodeList, C.int(nodeCount))
	count := C.RippleCalculateNodesToSync(overlay, buffer, message, nodeList, nodeList)
	fmt.Printf("RippleCalculateNodesToSync() count = %d\n", int(count))
	count = C.RippleCalculateNodesToCollectAck(overlay, buffer, message)
	fmt.Printf("RippleCalculateNodesToCollectAck() count = %d\n", int(count))
	C.RippleDeleteOverlay(overlay)

	overlay = C.RippleCreateTreeOverlay(C.int(3))
	C.RippleBuildOverlay(overlay, nodeList, C.int(nodeCount))
	count = C.RippleCalculateNodesToSync(overlay, buffer, message, nodeList, nodeList)
	fmt.Printf("RippleCalculateNodesToSync() count = %d\n", int(count))
	count = C.RippleCalculateNodesToCollectAck(overlay, buffer, message)
	fmt.Printf("RippleCalculateNodesToCollectAck() count = %d\n", int(count))
	C.RippleDeleteOverlay(overlay)
}

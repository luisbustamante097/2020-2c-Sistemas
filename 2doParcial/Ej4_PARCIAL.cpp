void ocurrencia(string A, string B){
    // Obtengo el inodo correspondiente al path A
    Ext2FSInode inode = inode_for_path(A);
    // Guardo el tamaño por bloque
    unsigned int tam_bloque = 1024 << superblock()->log_block_size;
    // Creo un buffer
	unsigned char* block_buf = new unsigned char[tam_bloque];
	
    // Variables para llevar la cuenta de donde estoy
	unsigned int total_read_bloque = 0;
	unsigned int total_read_file = 0;
    // Tamaño del archivo
	unsigned int file_size = inode->size;
	
	for (unsigned int i = 0; i < inode->blocks; i++){
		//Obtenemos el bloque i del inodo
		read_block(get_block_address(inode, i), block_buf);
		total_read_bloque = 0;
		do{
            // Casteamos correctamente a Ext2FSDirEntry lo que esta en el buffer
			Ext2FSDirEntry * dir_entry = (Ext2FSDirEntry *) block_buf;
            // SI el tipo del archivo es regular
			if (dir_entry->file_type == EXT2_FT_REG_FILE){
				string file_name = dir_entry->name;
                // Obtengo el inodo correspondiente al path del archivo
                Ext2FSInode inode = inode_for_path(A + "/" + file_name);
                // Uso una funcion auxiliar que se encargue de buscar dentro del archivo
                search_in_file(inode, B);
			}
			// Actualizo los valores de las variables de control
			total_read_file += dir_entry->record_length;
			total_read_bloque += dir_entry->record_length;
            // Actualizo el valor de block_buf ya que quiero moverme al siguiente dir entry
			block_buf += dir_entry->record_length;
			
		}while(total_read_bloque < tam_bloque || total_read_file < file_size);
	}
	free(block_buf);
}

void search_in_file(Ext2FSInode &inode, string B){
    // Guardo el tamaño por bloque
    unsigned int tam_bloque = 1024 << superblock()->log_block_size;
    // Creo un buffer
	unsigned char* block_buf = new unsigned char[tam_bloque];
	
    // Variables para llevar la cuenta de donde estoy
	unsigned int total_read_bloque = 0;
	unsigned int total_read_file = 0;
    // Tamaño del archivo
	unsigned int file_size = inode->size;
	
	for (unsigned int i = 0; i < inode->blocks; i++){
		//Obtenemos el bloque i del inodo
		read_block(get_block_address(inode, i), block_buf);
		total_read_bloque = 0;
		do{
            // Casteo el buffer al tamaño del string B
            string s = cortar_string(block_buf, B.size())
            // Busco por B dentro de este bloque
            if(B == S){
                printf("Encontre archivo");
            }
            
			// Actualizo los valores de las variables de control
			total_read_file += B.size;
			total_read_bloque += B.size;
            // Actualizo el valor de block_buf ya que quiero moverme al siguiente dir entry
			block_buf += B.size;
			
		}while(total_read_bloque < tam_bloque || total_read_file < file_size);
	}
	free(block_buf);
}
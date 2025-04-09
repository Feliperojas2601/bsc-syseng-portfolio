import { CommonModule } from '@angular/common';
import { Component } from '@angular/core';
import { FormsModule } from '@angular/forms';
import neo4j from 'neo4j-driver';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css'], 
  standalone: true,
  imports: [
    CommonModule, 
    FormsModule,
  ]
})
export class AppComponent {
  query: string = '';
  results: any[] = [];
  driver: any;
  driverConnected: boolean = false;

  constructor() {
    this.driver =  neo4j.driver("neo4j://localhost:7687");
    if (this.driver){
      this.driverConnected = true;
    }
  }

  findPerson() {
    const session = this.driver.session();
    const query = "MATCH (p:Persona) WHERE p.nombre = '" + this.query + "' RETURN p"
    console.log('Query:', query);
    session.run(query).then((result: { records: any[]; }) => {
      this.results = result.records.map((record: { toObject: () => any; }) => record.toObject());
      console.log('Results:', this.results);
      session.close();
    }).catch((error: any) => {
      console.error('Error executing query:', error);
      session.close();
    });
  }  
}

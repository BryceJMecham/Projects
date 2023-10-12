import { Component, Output, EventEmitter } from '@angular/core';

@Component({
  selector: 'app-map-ui',
  templateUrl: './map-ui.component.html',
  styleUrls: ['./map-ui.component.css']
})
export class MapUiComponent {
  @Output() submitted = new EventEmitter<string>();

  displayInfo(country: string){
    this.submitted.emit(country);
  }
}

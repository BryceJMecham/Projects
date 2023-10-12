import { Component, Input } from '@angular/core';

@Component({
  selector: 'app-info-list',
  templateUrl: './info-list.component.html',
  styleUrls: ['./info-list.component.css']
})
export class InfoListComponent {
  @Input() info = [];
  @Input() countryName = '';
  @Input() capital = '';
  @Input() continentName = '';
  @Input() population = '';
  @Input() errorMsg = '';
  @Input() region = '';
  @Input() income = '';
}
